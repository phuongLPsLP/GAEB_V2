#pragma once

#include <afxstr.h>  

struct Item_data
{
	CString Full_Langtext_data;
	CString Full_Kurztext_data;
	CString OZ;			//Ordnungszahl
	CString Qty;		//Menge
	CString QU;			//Einheit
	CString UP;			//Einheitpreis
	CString UP1;		//Teilpreis 1
	CString UP2;		//Teilpreis 2
	CString UP3;		//Teilpreis 3
	CString UP4;		//Teilpreis 4
	CString UP5;		//Teilpreis 5
	CString UP6;		//Teilpreis 6
	CString IT;			//Gesamtpreis
	CString TimeQu;		//Zeitansatz
	CString Total;
	CString DiscountAnteil;			//Nachlass Anteil
	CString DiscountPauschal;		//Nachlass Pauschal
};