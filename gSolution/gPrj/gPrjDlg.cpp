﻿
// gPrjDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "gPrj.h"
#include "gPrjDlg.h"
#include "afxdialogex.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") // 콘솔창 띄우기

using namespace std;
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgPrjDlg 대화 상자



CgPrjDlg::CgPrjDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GPRJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_TEST, &CgPrjDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_PRC, &CgPrjDlg::OnBnClickedBtnPrc)
	ON_BN_CLICKED(IDC_BTN_PATTERN, &CgPrjDlg::OnBnClickedBtnPattern)
	ON_BN_CLICKED(IDC_BTN_GET_DATA, &CgPrjDlg::OnBnClickedBtnGetData)
	ON_BN_CLICKED(IDC_BTN_THREAD, &CgPrjDlg::OnBnClickedBtnThread)
END_MESSAGE_MAP()


// CgPrjDlg 메시지 처리기

BOOL CgPrjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//윈도우 크기 조절
	MoveWindow(0, 0, 1280, 720);
	// 모달리스 다이얼로그 생성
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_CDlgImage, this); //(자식ID, 부모Window) 이거써줘야 접근 가능
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, 640, 480);

	// 모달리스 다이얼로그 생성
	m_pDlgImgRes = new CDlgImage;
	m_pDlgImgRes->Create(IDD_CDlgImage, this); //(자식ID, 부모Window) 이거써줘야 접근 가능
	m_pDlgImgRes->ShowWindow(SW_SHOW);
	m_pDlgImgRes->MoveWindow(640, 0, 640, 480);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CgPrjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CgPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CgPrjDlg::OnDestroy()
{
	//메모리 leak 제거 - new 쓰면 delete 해주기
	CDialogEx::OnDestroy();
	if (m_pDlgImage)	delete m_pDlgImage;
	if (m_pDlgImgRes)	delete m_pDlgImgRes;
}


void CgPrjDlg::callFunc(int n)
{
	//int nData = n;
	std::cout << n << std::endl;
}


void CgPrjDlg::OnBnClickedBtnTest()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	memset(fm, 0, nWidth*nHeight); // 초기화 안해주면 포인트데이터 100개씩 추가됨

	//랜덤하게 xy 포인트 만들어서 이미지 포인터에 넣음
	for (int k = 0; k < MAX_POINT; k++) { // 점 100개
		int x = rand() % nWidth;
		int y = rand() % nHeight;
		fm[y * nPitch + x] = rand()%0xff;
	}

	// 포인트 데이터 넣음
	int nIndex = 0;
	int nTh = 100;
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			if (fm[j * nPitch + i] > nTh) {
				if (m_pDlgImgRes->m_nDataCount < MAX_POINT) {
					m_pDlgImgRes->m_ptData[nIndex].x = i;
					m_pDlgImgRes->m_ptData[nIndex].y = j;
					m_pDlgImgRes->m_nDataCount = ++nIndex;
					
				}
			}
				
		}
	}
	m_pDlgImage->Invalidate(); //화면에 업데이트, onpaint함수 콜
	m_pDlgImgRes->Invalidate();
}


#include "CProcess.h"
#include <chrono>
#include <thread>
using namespace std;
using namespace chrono;

void CgPrjDlg::OnBnClickedBtnPrc()
{
	CProcess process;
	auto start = system_clock::now(); //auto : 변수형태 일단은 정하지 않겠다.
	int nRet = process.getStarInfo(&m_pDlgImage->m_image);
	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end-start);
	cout << nRet << "\t" << millisec.count() << "ms" << endl;
}

//패턴만들기
void CgPrjDlg::OnBnClickedBtnPattern()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	memset(fm, 0, nWidth * nHeight); // 초기화 안해주면 포인트데이터 추가됨

	CRect rect(100, 100, 200, 200);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			fm[j * nPitch + i] = rand()%0xff;
		}
	}
	m_pDlgImage->Invalidate();
}

//중심찾기
void CgPrjDlg::OnBnClickedBtnGetData()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	int nTH = 0x80;

	CRect rect(0, 0, nWidth, nHeight);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] > nTH) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}

	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	cout << dCenterX << "\t" << dCenterY << endl;
}

// 스레드
void threadProcess(CWnd* pParent, CRect rect, int* nRet) // global로 선언
{
	CgPrjDlg* pWnd = (CgPrjDlg*)pParent;
	*nRet = pWnd->processImg(rect); // parent에서 processImg
}

void CgPrjDlg::OnBnClickedBtnThread()
{
	auto start = system_clock::now();

	int imgSize = 4096 * 4;

	CRect rect(0, 0, imgSize, imgSize);
	CRect rt[4];

	int nRet[4] = { 0,0,0,0 };
	/*
	rt[0].SetRect(0, 0, imgSize, imgSize);
	rt[1].SetRect(imgSize, 0, imgSize*2, imgSize);
	rt[2].SetRect(0, imgSize, imgSize, imgSize*2);
	rt[3].SetRect(imgSize, imgSize, imgSize*2, imgSize*2);
	*/
	for (int k = 0; k < 4; k++) {
		rt[k] = rect;
		rt[k].OffsetRect(imgSize * (k%2), imgSize * int(k/2)); // OffsetRect : x축, y축으로 일정 영역만큼 움직여라
	}

	thread _thread0(threadProcess, this, rt[0], &nRet[0]); // thread call
	thread _thread1(threadProcess, this, rt[1], &nRet[1]);
	thread _thread2(threadProcess, this, rt[2], &nRet[2]);
	thread _thread3(threadProcess, this, rt[3], &nRet[3]);

	_thread0.detach();
	_thread1.detach();
	_thread2.detach();
	_thread3.detach();

	int nSum = 0;
	for (int i = 0; i < 4; i++)
		nSum += nRet[i];

	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);

	cout << "main: " << nSum << "\t" << millisec.count() * 0.001 << "sec" << endl;
}

int CgPrjDlg::processImg(CRect rect)
{
	auto start = system_clock::now();
	CProcess process;
	int nRet = process.getStarInfo(&m_pDlgImage->m_image, 0, rect);

	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);

	cout << "thread : " << nRet << "\t" << millisec.count() * 0.001 << "sec" << endl;

	return nRet;
}