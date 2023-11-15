#pragma once
#include "afxdialogex.h"

#define MAX_POINT 100
// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

	CImage m_image;
	CWnd* m_pParent; // CWnd 형태의 mpP 멤버변수로서 기억하게 만들어놓기
	int m_nDataCount = 0; // 그릴 점 개수
	CPoint m_ptData[MAX_POINT]; // CPoint : mfc에서 제공하는 xy좌표 형태

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnUp();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
private:
	void InitImage();
	void drawData(CDC* pDC);
};
