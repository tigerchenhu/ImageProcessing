#pragma once
#include <opencv2\opencv.hpp>

// MedianFilter 对话框

class MedianFilter : public CDialogEx
{
	DECLARE_DYNAMIC(MedianFilter)

public:
	MedianFilter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MedianFilter();

// 对话框数据
	enum { IDD = IDD_DIALOG_MEDIAN_FILTER };
	cv::Mat old_img;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
};

void insertion_sort(uchar *a, long length);