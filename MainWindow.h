#pragma once
#include "Win.h"
#include "Graphics.h"
#include "Exceptions.h"
#include <string>

// for granting special access to hWnd only for Graphics constructor
class HWNDKey{
	friend Graphics::Graphics( HWNDKey& );
public:
	HWNDKey( const HWNDKey& ) = delete;
	HWNDKey& operator=( HWNDKey& ) = delete;
protected:
	HWNDKey() = default;
protected:
	HWND hWnd = nullptr;
};

class MainWindow : public HWNDKey{
public:
	class Exception : public Exceptions{
	public:
		using Exceptions::Exceptions;
		virtual std::wstring GetFullMessage() const override { return GetNote() + L"\nAt: " + GetLocation(); }
		virtual std::wstring GetExceptionType() const override { return L"Windows Exception"; }
	};
public:
	MainWindow( HINSTANCE hInst,wchar_t* pArgs );
	MainWindow( const MainWindow& ) = delete;
	MainWindow& operator=( const MainWindow& ) = delete;
	~MainWindow();
	bool IsActive() const;
	bool IsMinimized() const;
	void ShowMessageBox( const std::wstring& title,const std::wstring& message,UINT type = MB_OK ) const;
	void Kill(){ PostQuitMessage( 0 ); }
	// returns false if quitting
	bool ProcessMessage();
	const std::wstring& GetArgs() const { return args; }
private:
	static LRESULT WINAPI _HandleMsgSetup( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam );
	static LRESULT WINAPI _HandleMsgThunk( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam );
	LRESULT HandleMsg( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam );
	static constexpr wchar_t* wndClassName = L"Main Title Window";
	HINSTANCE hInst = nullptr;
	std::wstring args;
};