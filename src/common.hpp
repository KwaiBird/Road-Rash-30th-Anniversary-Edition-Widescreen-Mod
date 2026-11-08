#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <bcrypt.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#pragma comment(lib,"bcrypt.lib")
inline std::wstring ModulePath(HMODULE m=nullptr){std::vector<wchar_t>b(32768);DWORD n=GetModuleFileNameW(m,b.data(),(DWORD)b.size());return n&&n<b.size()?std::wstring(b.data(),n):L"";}
inline std::wstring Dir(const std::wstring&p){return p.substr(0,p.find_last_of(L"\\/"));}
inline std::wstring Base(const std::wstring&p){return p.substr(p.find_last_of(L"\\/")+1);}
inline std::string HashFile(const std::wstring&p){BCRYPT_ALG_HANDLE a=nullptr;BCRYPT_HASH_HANDLE h=nullptr;HANDLE f=INVALID_HANDLE_VALUE;std::string out;std::vector<UCHAR>obj;DWORD n=0,len=0;UCHAR digest[32],buf[65536];if(BCryptOpenAlgorithmProvider(&a,BCRYPT_SHA256_ALGORITHM,nullptr,0)<0)goto done;if(BCryptGetProperty(a,BCRYPT_OBJECT_LENGTH,(PUCHAR)&len,sizeof len,&n,0)<0)goto done;obj.resize(len);if(BCryptCreateHash(a,&h,obj.data(),len,nullptr,0,0)<0)goto done;f=CreateFileW(p.c_str(),GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,0,nullptr);if(f==INVALID_HANDLE_VALUE)goto done;for(;;){if(!ReadFile(f,buf,sizeof buf,&n,nullptr))goto done;if(!n)break;if(BCryptHashData(h,buf,n,0)<0)goto done;}if(BCryptFinishHash(h,digest,32,0)>=0){std::ostringstream s;for(auto c:digest)s<<std::hex<<std::setfill('0')<<std::setw(2)<<(unsigned)c;out=s.str();}done:if(f!=INVALID_HANDLE_VALUE)CloseHandle(f);if(h)BCryptDestroyHash(h);if(a)BCryptCloseAlgorithmProvider(a,0);return out;}
constexpr char GameHash[]="9e40e25737149ab095061b7154797a35495faea97644fafc5a1e616f1400c968";
