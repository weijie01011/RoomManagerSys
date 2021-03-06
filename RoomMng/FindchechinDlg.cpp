// FindchechinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomMng.h"
#include "FindchechinDlg.h"
#include "afxdialogex.h"

/////////////////////////////////////////////////////////////////////////////
// CFindchechinDlg dialog

IMPLEMENT_DYNAMIC(CFindchechinDlg, CDialog)

	CFindchechinDlg::CFindchechinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindchechinDlg::IDD, pParent)
	, m_findcheckin_name(_T(""))
{

}

CFindchechinDlg::~CFindchechinDlg()
{
}

void CFindchechinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_findcheckin_name, m_findcheckin_name);
	DDX_Control(pDX, IDC_LIST1, m_findcheckin_list);
}


BEGIN_MESSAGE_MAP(CFindchechinDlg, CDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindchechinDlg message handlers


BOOL CFindchechinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	//设置列表框的颜色
	m_findcheckin_list.SetTextColor(RGB (0, 0, 0));
	m_findcheckin_list.SetTextBkColor(RGB (140, 180, 20));
	//初始化列表框内容
	m_findcheckin_list.InsertColumn(0,"凭证号码");
	m_findcheckin_list.InsertColumn(1,"姓名");
	m_findcheckin_list.InsertColumn(2,"身份证号码");
	m_findcheckin_list.InsertColumn(3,"联系电话");
	m_findcheckin_list.InsertColumn(4,"房间号");
	m_findcheckin_list.InsertColumn(5,"房间类型");
	m_findcheckin_list.InsertColumn(6,"客房价格");
	m_findcheckin_list.InsertColumn(7,"入住时间");
	m_findcheckin_list.InsertColumn(8,"住宿天数");
	m_findcheckin_list.InsertColumn(9,"宿费");
	m_findcheckin_list.InsertColumn(10,"折扣");
	m_findcheckin_list.InsertColumn(11,"应收宿费");
	m_findcheckin_list.InsertColumn(12,"押金");
	m_findcheckin_list.InsertColumn(13,"备注");

	RECT rect;
	m_findcheckin_list.GetWindowRect(&rect);
	int wid=rect.right-rect.left;
	m_findcheckin_list.SetColumnWidth(0,wid/9);
	m_findcheckin_list.SetColumnWidth(1,wid/9);
	m_findcheckin_list.SetColumnWidth(2,wid/9);
	m_findcheckin_list.SetColumnWidth(3,wid/9);
	m_findcheckin_list.SetColumnWidth(4,wid/9);
	m_findcheckin_list.SetColumnWidth(5,wid/9);
	m_findcheckin_list.SetColumnWidth(6,wid/9);
	m_findcheckin_list.SetColumnWidth(7,wid/9);
	m_findcheckin_list.SetColumnWidth(8,wid/9);
	m_findcheckin_list.SetColumnWidth(9,wid/9);
	m_findcheckin_list.SetColumnWidth(10,wid/9);
	m_findcheckin_list.SetColumnWidth(11,wid/9);
	m_findcheckin_list.SetColumnWidth(12,wid/9);
	m_findcheckin_list.SetColumnWidth(13,wid/9);

	//设置列表框风格
	m_findcheckin_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// 使用ADO创建数据库记录集
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	

	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 
	try//打开数据库
	{
		m_pRecordset->Open("SELECT * FROM checkintable",  // 查询 表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//捕获异常
	{
		AfxMessageBox(e->ErrorMessage());
	}
	try
	{
		if(!m_pRecordset->BOF)//判断指针是否在数据集最后
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox("表内数据为空");
			return false;
		}
	}
	catch(_com_error *e)//捕获异常
	{
		AfxMessageBox(e->ErrorMessage());
	}
	// 从数据库中读取数据并展现到 List 中
	showinList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CFindchechinDlg::showinList() {
	_variant_t var;
	int i=0;
	// read data from the database table 
	while(!m_pRecordset->adoEOF)
	{   //读取数据表中凭证号码字段数据
		var = m_pRecordset->GetCollect("凭证号码");
		if(var.vt != VT_NULL)
			m_regnumber = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.InsertItem(i,m_regnumber.GetBuffer(50));
		//读取数据表中姓名字段数据
		var = m_pRecordset->GetCollect("姓名");
		if(var.vt != VT_NULL)
			m_gustname = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,1,m_gustname.GetBuffer(50));
		//读取数据表中证件号码字段数据
		var = m_pRecordset->GetCollect("身份证号码");
		if(var.vt != VT_NULL)
			m_zhengjian_number = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,2,m_zhengjian_number.GetBuffer(50));
		//读取数据表中出差事由字段数据
		var = m_pRecordset->GetCollect("联系电话");
		if(var.vt != VT_NULL)
			m_telNumber = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,3,m_telNumber.GetBuffer(50));
		//读取数据表中房间号字段数据
		var = m_pRecordset->GetCollect("房间号");
		if(var.vt != VT_NULL)
			m_roomnumber = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,4,m_roomnumber.GetBuffer(50));
		//读取数据表中客房类型字段数据
		var = m_pRecordset->GetCollect("客房类型");
		if(var.vt != VT_NULL)
			m_roomlevel = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,5,m_roomlevel.GetBuffer(50));
		//读取数据表中客房价格字段数据
		var = m_pRecordset->GetCollect("房间价格");
		if(var.vt != VT_NULL)
			m_room_money = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,6,m_room_money.GetBuffer(50));
		//读取数据表中住宿日期字段数据
		var = m_pRecordset->GetCollect("入住时间");
		if(var.vt != VT_NULL)
			m_checkindate = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,7,m_checkindate.GetBuffer(50));
		//读取数据表中住宿天数字段数据
		var = m_pRecordset->GetCollect("住宿天数");
		if(var.vt != VT_NULL)
			m_checkdays = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,8,m_checkdays.GetBuffer(50));
		//读取数据表中宿费字段数据
		var = m_pRecordset->GetCollect("宿费");
		if(var.vt != VT_NULL)
			m_pre_discount = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,9,m_pre_discount.GetBuffer(50));
		//读取数据表中折扣字段数据
		var = m_pRecordset->GetCollect("折扣");
		if(var.vt != VT_NULL)
			m_pre_discount = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,10,m_pre_discount.GetBuffer(50));
		//读取数据表中应收宿费字段数据
		var = m_pRecordset->GetCollect("应收宿费");
		if(var.vt != VT_NULL)
			m_realmoney = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,11,m_realmoney.GetBuffer(50));
		//读取数据表中押金字段数据
		var = m_pRecordset->GetCollect("押金");
		if(var.vt != VT_NULL)
			m_pre_handinmoney = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,12,m_pre_handinmoney.GetBuffer(50));
		//读取数据表中备注字段数据
		var = m_pRecordset->GetCollect("备注");
		if(var.vt != VT_NULL)
			m_beizhu = (LPCSTR)_bstr_t(var);
		//在列表框内显示
		m_findcheckin_list.SetItemText(i,13,m_beizhu.GetBuffer(50));

		i++;
		m_pRecordset->MoveNext();//移动到下一条记录
	}


	// 关闭记录集
	m_pRecordset->Close();
	m_pRecordset = NULL;


	//更新显示
	UpdateData(false);
}


void CFindchechinDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(true);

	// 使用ADO创建数据库记录集
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息
	m_findcheckin_list.DeleteAllItems();
	CString strsqlfind;
	strsqlfind.Format("SELECT * FROM checkintable where 姓名='%s'",m_findcheckin_name);
	try
	{//打开数据库
		m_pRecordset->Open((_variant_t)(strsqlfind),                // 查询 表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//捕获打开数据库时候的异常
	{
		AfxMessageBox(e->ErrorMessage());
	}

	if(!m_pRecordset->BOF)//判断指针是否在数据集最后
		m_pRecordset->MoveFirst();
	else
	{
		AfxMessageBox("没有该记录！");
		return;
	}

	// 从数据库中读取数据并展现到 List 中
	showinList();
	//CDialog::OnOK();
}
