#pragma once
#include <opencv2\opencv.hpp>

// CGaussianBlur 对话框

class CGaussianBlur : public CDialogEx
{
	DECLARE_DYNAMIC(CGaussianBlur)

public:
	CGaussianBlur(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGaussianBlur();

// 对话框数据
	enum { IDD = IDD_DIALOG_GAUSSIAN_BLUR };
	cv::Mat old_img;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

inline double gaussian_function(double x, double y, double delta);