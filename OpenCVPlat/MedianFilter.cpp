// MedianFilter.cpp : 实现文件
//

#include "stdafx.h"
#include "OpenCVPlat.h"
#include "MedianFilter.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "OpenCVPlatDoc.h"
#include "OpenCVPlatView.h"


// MedianFilter 对话框

IMPLEMENT_DYNAMIC(MedianFilter, CDialogEx)

MedianFilter::MedianFilter(CWnd* pParent /*=NULL*/)
	: CDialogEx(MedianFilter::IDD, pParent)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	COpenCVPlatDoc *pDoc = (COpenCVPlatDoc*)pMain->GetActiveDocument();
	old_img = pDoc->image.clone();
}

MedianFilter::~MedianFilter()
{
}

void MedianFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MedianFilter, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// MedianFilter 消息处理程序


void MedianFilter::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CSliderCtrl *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_MEDIAN_FILTER);
	int value = pSlidCtrl->GetPos();
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	COpenCVPlatDoc *pDoc = (COpenCVPlatDoc*)pMain->GetActiveDocument();
	COpenCVPlatView *pView = (COpenCVPlatView*)pMain->GetActiveView();
	int window_size = 2 * value + 1;
	uchar *b = new uchar[window_size * window_size];
	uchar *g = new uchar[window_size * window_size];
	uchar *r = new uchar[window_size * window_size];
	int height = pDoc->image.size().height;
	int width = pDoc->image.size().width;
	if (pDoc->image.channels() == 3)
	{
		for (int row = 0; row < height; row++)
		{
			uchar *data = pDoc->image.ptr<uchar>(row);
			for (int col = 0; col < width; col++)
			{
				int count = 0;
				for (int i = row - window_size / 2; i <= row + window_size / 2; i++)
				for (int j = col - window_size / 2; j <= col + window_size / 2; j++)
				{
					if (i >= 0 && i < height &&
						j >= 0 && j < width)
					{
						uchar *old_data = old_img.ptr<uchar>(i);
						b[count] = old_data[j * 3];
						g[count] = old_data[j * 3 + 1];
						r[count] = old_data[j * 3 + 2];
						count++;
					}
				}
				insertion_sort(b, count);
				insertion_sort(g, count);
				insertion_sort(r, count);
				data[col * 3] = b[count / 2];
				data[col * 3 + 1] = g[count / 2];
				data[col * 3 + 2] = r[count / 2];
			}
		}
	}
	else
	{
		for (int row = 0; row < height; row++)
		{
			uchar *data = pDoc->image.ptr<uchar>(row);
			for (int col = 0; col < width; col++)
			{
				int count = 0;
				for (int i = row - window_size / 2; i <= row + window_size / 2; i++)
				for (int j = col - window_size / 2; j <= col + window_size / 2; j++)
				{
					if (i >= 0 && i < height &&
						j >= 0 && j < width)
					{
						uchar *old_data = old_img.ptr<uchar>(i);
						b[count] = old_data[j];
						count++;
					}
				}
				insertion_sort(b, count);
				data[col] = b[count / 2];
			}
		}
	}
	
	delete[] b;
	delete[] g;
	delete[] r;
	pView->Invalidate();
}


BOOL MedianFilter::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CSliderCtrl *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_MEDIAN_FILTER);
	pSlidCtrl->SetRange(0, 5);
	pSlidCtrl->SetTicFreq(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//Insertion sort
void insertion_sort(uchar *a, long length)
{
	for (long i = 1; i < length; i++)
	{
		long b = a[i];
		long j;
		for (j = i - 1; j >= 0; j--)
		{
			if (a[j] > b) a[j + 1] = a[j];
			else break;
		}
		a[j + 1] = b;
	}
}