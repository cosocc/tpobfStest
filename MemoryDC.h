#pragma once
class CMemoryDC :public CDC
{
	CSize m_size;
public:
	int GetWidth() const
	{
		return m_size.cx;
	}
	int GetHeight() const
	{
		return m_size.cy;
	}
	void MakeRgn(CRgn& rgn, COLORREF clTrans)
	{//��ͼ�ĺ���   ֻ�ܿ۴�ɫ�ı���ͼ
		//����Ŀ��  ���Դ˷���
		rgn.DeleteObject();
		rgn.CreateRectRgn(0, 0, 0, 0);
		int i = m_size.cx;
		while (i-- > 0)
		{
			int j = m_size.cy;
			while (j-- > 0)
			{
				auto col = GetPixel(i, j);
				if (clTrans != col)
				{
					CRgn r;
					r.CreateRectRgn(i, j, i + 1, j + 1);
					rgn.CombineRgn(&rgn, &r, RGN_OR);
				}
			}
		}
	}
	void BitTrans(
		int nXDest,		// Ŀ�����X
		int nYDest,		// Ŀ�����Y
		int nWidthDest,	// Ŀ����
		int nHeightDest,// Ŀ��߶�
		CDC* pDC,		// Ŀ��DC
		int nXSrc,		// ��Դ���X
		int nYSrc,		// ��Դ���Y
		COLORREF crTrans// ͸��ɫ
	)
	{
		CMemoryDC dcImage(nWidthDest, nHeightDest, pDC);//��ʱDC
		CBitmap bmpMask;
		bmpMask.CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);            // ������ɫ����λͼ
		CDC dcMask;//����DC 
		dcMask.CreateCompatibleDC(pDC);
		dcMask.SelectObject(bmpMask);
		//������λͼ���ڴ�DC�е�λͼ����������ʱDC��
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, this, nXSrc, nYSrc, SRCCOPY);
		//ԭͼ
		pDC->BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);


		// ������ʱDC��͸��ɫ
		dcImage.SetBkColor(crTrans);
		//����DC��͸������Ϊ��ɫ��������Ϊ��ɫ
		dcMask.BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);
		//�����ǰ׵׺�ͼ
		pDC->BitBlt((nWidthDest + 10) * 1, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCCOPY);

		//��ʱDC͸������Ϊ��ɫ���������򱣳ֲ���
		dcImage.SetBkColor(RGB(0, 0, 0));
		dcImage.SetTextColor(RGB(255, 255, 255));
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);

		//�ڵײ�ͼ
		pDC->BitBlt(2 * (nWidthDest + 10), 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);

		//͸����ͼ
		pDC->BitBlt(3 * (nWidthDest + 10), 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);   //��ʵ�����ǰ�λ������&

		// Ŀ��DC͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		//����ͼ
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);
		//͸����ͼ+��������ͼ  ����������ʾ
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCPAINT);           //�����ǰ�λ��|����
	}
	void StretchTrans(//����Ŀ��  ���Դ˷���
		int nXDest,			// Ŀ�����X
		int nYDest,			// Ŀ�����Y
		int nWidthDest,     // Ŀ����
		int nHeightDest,    // Ŀ��߶�
		CDC* pDC,			// Ŀ��DC
		int nXSrc,			// ��Դ���X
		int nYSrc,			// ��Դ���Y
		int nWidthSrc,		// ��Դ���
		int nHeightSrc,		// ��Դ�߶�
		COLORREF crTrans	// ͸��ɫ
	)
	{
		CMemoryDC dcImage(nWidthDest, nHeightDest, pDC);//��ʱDC
		CBitmap bmpMask;
		// ������ɫ����λͼ
		bmpMask.CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);
		CDC dcMask;
		dcMask.CreateCompatibleDC(pDC);
		dcMask.SelectObject(bmpMask);
		dcImage.SetStretchBltMode(HALFTONE);
		// ������λͼ���ڴ�DC�е�λͼ����������ʱDC��
		if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
			dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, this, nXSrc, nYSrc, SRCCOPY);
		else
			dcImage.StretchBlt(0, 0, nWidthDest, nHeightDest,
				this, nXSrc, nYSrc, nWidthSrc, nHeightSrc, SRCCOPY);

		// ������ʱDC��͸��ɫ
		dcImage.SetBkColor(crTrans);
		//����DC��͸������Ϊ��ɫ��������Ϊ��ɫ
		dcMask.BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);

		//��ʱDC͸������Ϊ��ɫ���������򱣳ֲ���
		dcImage.SetBkColor(RGB(0, 0, 0));
		dcImage.SetTextColor(RGB(255, 255, 255));
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);

		// Ŀ��DC͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCPAINT);
	}
	BOOL LoadBitmap(UINT nID, CDC* pDC = NULL)
	{
		CBitmap bmp;
		if (!bmp.LoadBitmap(nID))
			return FALSE;

		if (!GetSafeHdc() && !CreateCompatibleDC(pDC))
			return FALSE;
		this->SelectObject(&bmp);
		BITMAP bm;
		bmp.GetBitmap(&bm);
		m_size.cx = bm.bmWidth;
		m_size.cy = bm.bmHeight;
		return TRUE;
	}

	BOOL Create(int cx, int cy, CDC* pDC = NULL)
	{
		CBitmap bmp;
		if (pDC)
		{
			if (!bmp.CreateCompatibleBitmap(pDC, cx, cy))
				return FALSE;
		}
		else
		{
			CClientDC dc(NULL);
			if (!bmp.CreateCompatibleBitmap(&dc, cx, cy))
				return FALSE;
		}
		if (!GetSafeHdc() && !CreateCompatibleDC(pDC))
			return FALSE;
		SelectObject(&bmp);
		m_size.cx = cx;
		m_size.cy = cy;
		return TRUE;
	}
	CMemoryDC(UINT nID, CDC* pDC = NULL)
	{
		LoadBitmap(nID, pDC);
	}

	BOOL LoadBitmap(LPCTSTR szBitmapFile, CDC* pDC = NULL)
	{
		HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, szBitmapFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (!hBitmap)
			return FALSE;
		BITMAP bm;
		GetObject(hBitmap, sizeof(bm), &bm);
		m_size.cx = bm.bmWidth;
		m_size.cy = bm.bmHeight;
		CreateCompatibleDC(pDC);
		SelectObject(hBitmap);
		DeleteObject(hBitmap);
		return TRUE;
	}
	CMemoryDC(LPCTSTR szBitmapFile, CDC* pDC = NULL)
	{
		LoadBitmap(szBitmapFile, pDC);
	}
	CMemoryDC(int cx, int cy, CDC* pDC = NULL)
	{
		Create(cx, cy, pDC);
	}
	CMemoryDC()
	{

	}
	~CMemoryDC()
	{

	}
};
