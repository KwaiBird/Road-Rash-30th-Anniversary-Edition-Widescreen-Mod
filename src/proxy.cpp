// x86 app-local DirectDraw proxy. DllMain (in mod.cpp) only records self.
#define WIDE_VERSION "0.2.2"
#include "mod.cpp"

static INIT_ONCE backendOnce=INIT_ONCE_STATIC_INIT;
static INIT_ONCE hooksOnce=INIT_ONCE_STATIC_INIT;
static HMODULE backend;
static FARPROC proxyExports[22];
static const char* const exportNames[]={
 "AcquireDDThreadLock","CompleteCreateSysmemSurface","D3DParseUnknownCommand",
 "DDGetAttachedSurfaceLcl","DDInternalLock","DDInternalUnlock","DSoundHelp",
 "DirectDrawCreate","DirectDrawCreateClipper","DirectDrawCreateEx",
 "DirectDrawEnumerateA","DirectDrawEnumerateExA","DirectDrawEnumerateExW",
 "DirectDrawEnumerateW","DllCanUnloadNow","DllGetClassObject",
 "GetDDSurfaceLocal","GetOLEThunkData","GetSurfaceFromDC","RegisterSpecialCase",
 "ReleaseDDThreadLock","SetAppCompatData"};

static BOOL CALLBACK LoadBackend(PINIT_ONCE,PVOID,PVOID*){
 wchar_t folder[MAX_PATH];UINT n=GetSystemDirectoryW(folder,MAX_PATH);
 if(!n||n>=MAX_PATH)return FALSE;
 std::wstring path=std::wstring(folder,n)+L"\\ddraw.dll";
 backend=LoadLibraryExW(path.c_str(),nullptr,LOAD_LIBRARY_SEARCH_SYSTEM32);
 if(!backend||backend==self)return FALSE;
 for(unsigned i=0;i<22;i++)proxyExports[i]=GetProcAddress(backend,exportNames[i]);
 return TRUE;
}
static BOOL CALLBACK InitializeHooks(PINIT_ONCE,PVOID,PVOID*){
 // Invoked synchronously by the game's first DirectDrawCreate, after DLL entry.
 // Unsupported EXEs retain system DirectDraw; they never receive game hooks.
 WidescreenInitialize(nullptr);
 return TRUE;
}
static void __cdecl EnsureExport(unsigned index){
 if(!InitOnceExecuteOnce(&backendOnce,LoadBackend,nullptr,nullptr)||!proxyExports[index]){
  MessageBoxW(nullptr,L"Unable to load the Windows system ddraw.dll or resolve a required export.",L"Road Rash Widescreen",MB_OK|MB_ICONERROR);
  ExitProcess(ERROR_PROC_NOT_FOUND);
 }
}
extern "C" HRESULT WINAPI ProxyDirectDrawCreate(GUID* guid,LPDIRECTDRAW* draw,IUnknown* outer){
 EnsureExport(7);
 InitOnceExecuteOnce(&hooksOnce,InitializeHooks,nullptr,nullptr);
 auto create=reinterpret_cast<HRESULT(WINAPI*)(GUID*,LPDIRECTDRAW*,IUnknown*)>(proxyExports[7]);
 return create(guid,draw,outer);
}
// Preserve the caller's registers, flags and stack; the real export owns its ABI.
#define FORWARD(name,index) extern "C" __declspec(naked) void Proxy##name(){ \
 __asm { pushfd } __asm { pushad } __asm { push index } \
 __asm { call EnsureExport } __asm { add esp,4 } \
 __asm { popad } __asm { popfd } __asm { jmp dword ptr [proxyExports+index*4] } }
FORWARD(AcquireDDThreadLock,0)
FORWARD(CompleteCreateSysmemSurface,1)
FORWARD(D3DParseUnknownCommand,2)
FORWARD(DDGetAttachedSurfaceLcl,3)
FORWARD(DDInternalLock,4)
FORWARD(DDInternalUnlock,5)
FORWARD(DSoundHelp,6)
FORWARD(DirectDrawCreateClipper,8)
FORWARD(DirectDrawCreateEx,9)
FORWARD(DirectDrawEnumerateA,10)
FORWARD(DirectDrawEnumerateExA,11)
FORWARD(DirectDrawEnumerateExW,12)
FORWARD(DirectDrawEnumerateW,13)
FORWARD(DllCanUnloadNow,14)
FORWARD(DllGetClassObject,15)
FORWARD(GetDDSurfaceLocal,16)
FORWARD(GetOLEThunkData,17)
FORWARD(GetSurfaceFromDC,18)
FORWARD(RegisterSpecialCase,19)
FORWARD(ReleaseDDThreadLock,20)
FORWARD(SetAppCompatData,21)
