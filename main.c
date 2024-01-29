/****************************************************************************
 *                                                                          *
 * File    : main.c                                                         *
 *                                                                          *
 * Purpose : Generic dialog based Win32 application.                        *
 *                                                                          *
 * History : Date      Reason                                               *
 *           17/03/07  Created                                              *
 *                                                                          *
 ****************************************************************************/

//*********************//
// Änderungsgeschichte //
//*********************//*****/
// aN / 27.03.2007 / 1.0.1.05 / Im Edit-Dialog alte Endzeit als Vorgabe anzeigen
// aN / 27.03.2007 / 1.0.1.06 / Aufruf für Edit-Dialog auf modal geändert
// aN / 10.04.2007 / 1.0.1.07 / Speichern und Wiederherstellen der Fensterposition
// aN / 10.04.2007 / 1.0.1.08 / Eine einfache Syntaxprüfung der Eingabe ergänzt
// aN / 10.04.2007 / 1.0.1.09 / Eine einfache Syntaxprüfung der Eingabe ergänzt
// aN / 10.04.2007 / 1.0.1.10 / Bei fscanf die Anzahl gelesener Parameter geprüft
// aN / 11.04.2007 / 1.0.1.11 / Farbcodes für die Restzeit
// aN / 11.04.2007 / 1.0.1.12 / Farben angepaßt und in SetColors gehoben
// aN / 16.04.2007 / 1.0.1.13 / Minimieren auf Klick-Rechts
// aN / 16.04.2007 / 1.0.1.14 / Experimente mit Menüs, AktOutput
// aN / 03.05.2007 / 1.0.1.15 / Anzeige umschaltbar bei Minimiert
// aN / 04.06.2007 / 1.0.1.16 / Bei minimiert, Endzeitdialog Systemmodal
// aN / 05.06.2007 / 1.0.1.17 / Alarmdialog
// aN / 14.03.2012 / 1.0.1.18 / Alarmdialog Modal und zentriert
// aN / 17.04.2012 / 1.0.1.19 / Grund für Alarm, Eingabe und Verwaltung
// aN / 30.07.2012 / 1.0.1.20 / Animiertes Tray-Icon
// aN / 31.07.2012 / 1.0.1.23 / Reduzierung des Aktualisieren der Anzeige
// aN / 31.07.2012 / 1.0.1.24 / Main-Icon an Anzeige anpassen
// aN / 01.08.2012 / 1.0.1.25 / GDI-Leak in TrayIcon-Erzeugung korrigiert
// aN / 01.08.2012 / 1.0.1.26 / GDI-Leak korrigiert 2.Versuch
// aN / 19.09.2012 / 1.0.1.27 / Anderes Format für Titelzeile
// aN / 05.10.2012 / 1.0.1.28 / Nochmals anderes Format für Titelzeile
// aN / 07.04.2023 / 1.0.1.29 / größeres Zeit-Icon
// aN / 15.04.2023 / 1.0.1.30 / Parameter Z(eit) und "Grund"
// aN / 28.06.2023 / 1.9.0.31 / Einlesen von ini und Parameter korrigiert
// aN / 30.06.2023 / 1.9.0.32 / INI folgt EXE-Namen
// aN / 01.07.2023 / 1.9.0.33 / Nur ein Edit-Dialog bei Doppelklick
// aN / 02.07.2023 / 1.9.0.34 / Bei Alarm Verlängerungsbuttons
// aN / 08.07.2023 / 1.9.0.35 / gemeinsame Daten in eine Struktur
// aN / 09.07.2023 / 1.9.0.36 / Uhren einzeln verstecken und wieder holen
// aN / 10.07.2023 / 1.9.0.37 / bei Alarm ein vierter Button Edit
// aN / 22.07.2023 / 1.9.0.38 / Fenster auf TopMost schalten
// aN / 27.07.2023 / 2.0.0.39 / Uhren differenzieren analog, digital, beides
// aN / 31.07.2023 / 2.0.0.40 / HPEN nach Gebrauch wieder löschen
// aN / 07.08.2023 / 2.0.0.41 / Parameter S(panne) auswerten
// aN / 09.08.2023 / 2.0.0.42 / Edit-Dialog überarbeitet
// aN / 14.08.2023 / 2.0.0.43 / Restzeit-Berechnung neu
// aN / 18.08.2023 / 2.0.0.44 / Farbrechnung und Farbe-Stundenzeiger neu
// aN / 21.08.2023 / 2.0.0.45 / Refresh ohne RDW_ERASE und wieder zurück
// aN / 05.09.2023 / 2.0.0.46 / Systemicon setzen mit WM_SETICON (64Bit-tauglich)
// aN / 11.09.2023 / 2.0.0.47 / Vorläufige Endversion
// aN / 14.09.2023 / 2.9.0.48 / WinUhrME, der Anfang
// aN / 15.09.2023 / 2.9.0.49 / Sound-Effekt ergänzt
// aN / 19.09.2023 / 3.0.0.50 / Ein guter Anfang
// aN / 20.09.2023 / 3.0.0.51 / Sortieren der Liste und trimmen von Texten
// aN / 22.09.2023 / 3.0.0.52 / Tastenkürzeltabelle eingebaut
// aN / 23.09.2023 / 3.0.0.53 / Info-Dialog eingebaut
// aN / 25.09.2023 / 3.0.0.54 / aktuelles Ereignis in Liste eintragen
// aN / 26.09.2023 / 3.0.0.55 / Parameter 'N' - starte mit nächsten Ereignis
// aN / 18.10.2023 / 3.0.0.56 / ToolTip für Alarmgrund eingebaut
// aN / 25.10.2023 / 3.0.0.57 / ToolTip ziemlich fertig
// aN / 27.10.2023 / 3.0.0.58 / Einige Bug-Fixes
// aN / 27.10.2023 / 3.0.0.60 / Einige kleine Änderungen
// aN / 17.11.2023 / 3.0.0.61 / Statusanzeige
// aN / 26.11.2023 / 3.0.0.62 / Statusanzeige per Menü/Tastendruck
// aN / 16.12.2023 / 3.9.0.63 / erste Wochentag-Funktionen gehen schon
// aN / 21.12.2023 / 3.9.0.64 / TimeToEvent schein zu funktionieren
// aN / 22.12.2023 / 3.9.0.65 / Listendialog mit Eintrag "sortiere"
// aN / 25.12.2023 / 3.9.0.66 / & bei div. Dialogen ergänzt
// aN / 25.12.2023 / 4.0.0.67 / neues Kleid
// aN / 29.12.2023 / 4.0.0.68 / einige Fixis
// aN / 09.01.2024 / 4.0.0.71 / TimeToEvent (hoffentlich) korrigiert
// aN / 09.01.2024 / 4.0.0.72 / Ini - lesen und schreiben verbessert
// aN / 10.01.2024 / 4.0.0.73 / neue Kleider (celeste)
// aN / 12.01.2024 / 4.0.0.74 / "Wt" fürs Wochenende korrigiert
// aN / 14.01.2024 / 4.0.0.75 / AdjustWT
// aN / 16.01.2024 / 4.0.0.76 / Statusanzeige bei Ton ein/aus
// aN / 20.01.2024 / 4.0.0.77 / Wt hoffentlich korrigiert
// aN / 23.01.2024 / 4.0.0.78 / GetList()/SetList()
// aN / 27.01.2024 / 4.0.0.79 / Reihenfolge der Zeiger der gr. Uhr ändern
// aN / 29.01.2024 / 4.0.0.80 / Infofenster per Tastendruck quittierbar

/*
 * Either define WIN32_LEAN_AND_MEAN, or one or more of NOCRYPT,
 * NOSERVICE, NOMCX and NOIME, to decrease compile time (if you
 * don't need these defines -- see windows.h).
 */

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <winuser.h>
#include <wingdi.h>
#include <tchar.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "main.h"

/** #defines ***************************************************************/

#define NELEMS(a)  (sizeof(a) / sizeof((a)[0]))
#define Refresh(A) RedrawWindow(A,NULL,NULL,RDW_ERASE|RDW_INVALIDATE|RDW_ALLCHILDREN|RDW_UPDATENOW);
#define RefreshX(A) RedrawWindow(A,NULL,NULL,RDW_INVALIDATE|RDW_ALLCHILDREN|RDW_UPDATENOW);

#define BUF_SIZE            256
#define ICONSIZE            40
#define IMAGESIZE           40
#define BIGICONSIZE         96
#define BIGIMAGESIZE        96
#define STUNDE_COLOR_AM     RGB(  0,  0,255)
#define STUNDE_COLOR_PM     RGB(  0,127,191)
#define MINUTE_COLOR        RGB(  0,127,  0)
#define SEKUNDE_COLOR       RGB(  0,  0,  0)
#define WECKER_COLOR_AM     RGB(255,  0,  0)
#define WECKER_COLOR_PM     RGB(191, 64,  0)
#define MASK_COLOR          RGB(255,255,255)
#define GCL_HICON           (-14)

/** Typen *******************************************************************/
typedef struct
{
    HWND hWnd;
    HMENU hSMenu;
    HWND hToolTip;
    int hide;
    int top;
    RECT rWndDlg;
} uhr;

typedef struct
{
    UINT8 std;
    UINT8 min;
    UINT8 sec;
    char wt[3];
    char grund[100];
} ereignis;

/** Prototypes **************************************************************/

static LRESULT CALLBACK DlgProcMain(HWND, UINT, WPARAM, LPARAM);
static LRESULT CALLBACK DlgProcEdit(HWND, UINT, WPARAM, LPARAM);
static LRESULT CALLBACK DlgProcAlarm(HWND, UINT, WPARAM, LPARAM);
static LRESULT CALLBACK DlgProcList(HWND, UINT, WPARAM, LPARAM);
static LRESULT CALLBACK DlgProcInfo(HWND, UINT, WPARAM, LPARAM);
static LRESULT CALLBACK DlgProcStatus(HWND, UINT, WPARAM, LPARAM);
BOOL PlayResource(LPSTR lpName);
int EventToEvent(ereignis *e1, ereignis *e2);
int TimeToEvent(char *wt, int h, int m, int s, ereignis *e);
void SetNextEvent(void);
void AktOutput(HWND hwndDlg);
void AktToolTip(void);
void SetColors(HWND hwndCtl, HDC wParam);
HBRUSH SetBkfColor(COLORREF TxtColr, COLORREF BkColr, HDC hdc);
void SaveRect(void);
void CalcRestZeit(SYSTEMTIME j, SYSTEMTIME e, SYSTEMTIME *r);
char *dotrim(char *string);
void AddTime(int diff);
void GetList(HWND hWnd);
void SetList(HWND hWnd);

/** Global variables ********************************************************/

static HANDLE ghInstance;
static COLORREF gBackgroundColor;
static COLORREF gForegroundColor;
static HICON hBackIcon;
static HICON hBigIcon;
static int show_rest = 1;
static int blackwhite = 0;
static char IniName[300] = "WinUhrWT.ini";
static ereignis ereignisse[10];

static HMENU hPopupMenu = NULL;
static NOTIFYICONDATA nid = {0};
static HICON hIcon;
static HICON hBIcon;

static TOOLINFO toolTip = { 0 };
//static HWND hToolTip;

int AlarmDlg = 0;  // Flag ob der Alarmdialog eingeschaltet ist
int erreicht = 0;  // Flag für Zeit erreicht
int sound_off = 0; // Sound on/off

SYSTEMTIME DZ = {2012, 0, 0,12,0,0,0,0};
SYSTEMTIME EZ = {2012, 3,14,17,0,0,0,0};
SYSTEMTIME RZ = {   0, 0, 0, 0,0,0,0,0};
char alarmgrund[100] = "";
char wochentag[3] = "  ";
char *wota[] = {"So\0Sonntag","Mo\0Montag","Di\0Dienstag","Mi\0Mittwoch","Do\0Donnerstag","Fr\0Freitag","Sa\0Samstag","Wt\0Werktag","We\0Wochenend"};

uhr uhren[3] = {{NULL,NULL,NULL,0,0,{0,0,0,0}},
                {NULL,NULL,NULL,0,0,{0,0,0,0}},
                {NULL,NULL,NULL,0,0,{0,0,0,0}}};

//! Sound-Ausgabe
BOOL PlayResource(LPSTR lpName)
{
    BOOL bRtn;
    LPSTR lpRes;
    HANDLE hResInfo, hRes;

    if (sound_off == 0)
    {
        // Find the WAVE resource.
        hResInfo = FindResource(GetModuleHandle(NULL), lpName, RT_RCDATA);
        if (hResInfo == NULL)
            return FALSE;

        // Load the WAVE resource.

        hRes = LoadResource(GetModuleHandle(NULL), hResInfo);
        if (hRes == NULL)
            return FALSE;

        // Lock the WAVE resource and play it.
        lpRes = LockResource(hRes);
        if (lpRes != NULL)
        {
            bRtn = sndPlaySound(lpRes, SND_MEMORY | SND_ASYNC);
        }
        else
        bRtn = 0;

        // Free the WAVE resource and return success or failure.

        FreeResource(hRes);
    }
    else
    bRtn = 0;

    return bRtn;
}

//****************************************************************************
//  Zeit zwischen zwei Events
//****************************************************************************
int EventToEvent(ereignis *e1, ereignis *e2)
{
    return (TimeToEvent(e1->wt,e1->std,e1->min,e1->sec,e2));
}

//****************************************************************************
//  Zeit bis zum Event
//****************************************************************************
int TimeToEvent(char *wt, int h, int m, int s, ereignis *e)
{
    int res = 0;
    long sts;  // Sekunden bis zum Start
    long ste;  // Sekunden bis zum Event
    int i;
    short sWt;
    int flag = 0;

    sts = ((h * 60) + m) * 60 + s;
    ste = ((e->std * 60) + e->min) * 60 + e->sec;

    for(i = 0; i < 7; i++)
    {
        if(strcmp(wota[i], wt) != 0)
        {
            sts += 24 * 3600;
            if(strcmp(wota[i], e->wt) == 0)
            {
                flag = 1;
            }
        }
        else
        {
            break;
        }
    }

    if(flag != 0)
    {
        ste += 168 * 3600;
    }

    sWt = e->wt[0] * 256 + e->wt[1];
    switch(sWt)
    {
        case 'So':
            ste += 0 * 24 * 60 * 60;
            break;
        case 'Mo':
            ste += 1 * 24 * 60 * 60;
            break;
        case 'Di':
            ste += 2 * 24 * 60 * 60;
            break;
        case 'Mi':
            ste += 3 * 24 * 60 * 60;
            break;
        case 'Do':
            ste += 4 * 24 * 60 * 60;
            break;
        case 'Fr':
            ste += 5 * 24 * 60 * 60;
            break;
        case 'Sa':
            ste += 6 * 24 * 60 * 60;
            break;
        case 'Wt':
            ste += 24 * 60 * 60;
            for(i = 1; i <= 5; i++)
            {
                if(ste > sts)
                    break;
                ste += 24 * 60 * 60;
            }
            if (6 == i)
            {
                ste += 2 * 24 * 60 * 60;
            }
            break;
        case 'We':
            if(ste > sts)
                break;
            ste += 6 * 24 * 60 * 60;
            if(ste > sts)
                break;
            ste += 1 * 24 * 60 * 60;
            break;
        case '  ':
            while(sts > ste)
            {
                ste += 24 * 60 * 60;
    }
            break;
        default:
            break;
    }
    res = ste - sts;
    if(res < 0)
        res += 7 * 24 * 60 * 60;

    return res % (7 * 24 * 60 * 60);
}

//****************************************************************************
//  Adjust WT
//****************************************************************************
char* AdjustWT(char *wt)
{
    int i;
    int found=0;

    dotrim(wt);
    strupr(wt+0);
    strlwr(wt+1);
    wt[2]=0;

    for(i=0; i<NELEMS(wota);i++)
    {
        if (strcmp(wt,wota[i]) == 0)
        {
            found = 1;
            break;
        }
    }

    if (!found)
    {
        wt[0] = ' ';
        wt[1] = ' ';
    }
    return wt;
}

//****************************************************************************
//  GetList
//****************************************************************************
void GetList(HWND hWnd)
{
    char hStr[100];
    int items;
    int h,m,s;

    // Alarm lesen
    GetDlgItemText(hWnd, IDD_ZEIT_AKT, hStr, 100);
    items = sscanf(hStr, "%d:%d:%d", &h, &m, &s);
    // eine Einfache Syntaxprüfung der Eingabe  ** aN 09.08.2023
    switch(items)
    {
    case 3:
        EZ.wHour = h % 24;
        EZ.wMinute = m % 60;
        EZ.wSecond = s % 60;
        erreicht = 0;
        break;
    case 2:
        EZ.wHour = h % 24;
        EZ.wMinute = m % 60;
        EZ.wSecond = 0;
        erreicht = 0;
        break;
    case 1:
        GetLocalTime(&EZ);
        EZ.wSecond = 0;
        AddTime(h);
        erreicht = 0;
        break;
    default:
        break;
    }

    GetDlgItemText(hWnd, IDD_EVENT_AKT, alarmgrund, 100);
    dotrim(alarmgrund);
    GetDlgItemText(hWnd, IDD_WOCHENTAG, hStr, 3);
    AdjustWT(hStr);
    strncpy(wochentag, hStr, 2);

    // Liste lesen
    for(int i = 0; i < 10; i++)
    {
        ereignis * e = &ereignisse[i];

        memset(e, 0, sizeof(ereignis));
        GetDlgItemText(hWnd, IDD_ZEIT_01 + i * 2, hStr, 100);
        sscanf(hStr, "%d:%d:%d", &h, &m, &s);
        e->std = (char)(h % 24);
        e->min = (char)(m % 60);
        e->sec = (char)(s % 60);
        GetDlgItemText(hWnd, IDD_EVENT_01 + i * 2, e->grund, 100);
        GetDlgItemText(hWnd, IDD_WT_01 + i, hStr, 100);
        dotrim(hStr);
        strupr(hStr);
        if(strchr(hStr, 'X') != NULL)
        {
            strcpy(e->wt, "  ");
            e->std = 0;
            e->min = 0;
            e->sec = 0;
            e->grund[0] = 0;
            continue;
        }
        AdjustWT(hStr);
        strncpy(e->wt, hStr, 2);
        //dotrim(e->grund);
    }
}

//****************************************************************************
//  SetList
//****************************************************************************
void SetList(HWND hWnd)
{
    char hStr[100];

    sprintf(hStr, "%02d:%02d:%02d", EZ.wHour, EZ.wMinute, EZ.wSecond);
    SetDlgItemText(hWnd, IDD_ZEIT_AKT, hStr);
    SetDlgItemText(hWnd, IDD_EVENT_AKT, alarmgrund);
    SetDlgItemText(hWnd, IDD_WOCHENTAG, wochentag);
    for (int i=0; i<10; i++)
    {
        ereignis e = ereignisse[i];
        SetDlgItemText(hWnd, IDD_EVENT_01+2*i, e.grund);
        sprintf(hStr, "%02d:%02d:%02d", e.std, e.min, e.sec);
        SetDlgItemText(hWnd, IDD_ZEIT_01+2*i, hStr);
        SetDlgItemText(hWnd, IDD_WT_01+i, e.wt);
    }
}

//****************************************************************************
//  Get Parameter
//****************************************************************************
void GetParams(char *szCmdline)
{
    int i = 0;
    char *cp;
    char hStr[200];

    if (szCmdline == NULL)
        return;

    while (szCmdline[i] != 0)
    {
        //TODO
        switch (szCmdline[i])
        {
            case '"': // Grund
                cp = alarmgrund;
                i++;
                while ((szCmdline[i] != '"') && (szCmdline[i] != 0))
                {
                    //TODO
                    *(cp++) = szCmdline[i++];
                }
                *cp = 0;
                break;

            case 'Z': // Zeitpunkt
            case 'z':
                i++;
                if (szCmdline[i] == '=')
                    i++;
                if (szCmdline[i] == ':')
                    i++;
                cp = hStr;
                while ((szCmdline[i] != ' ') && (szCmdline[i] != '\0'))
                    *(cp++) = szCmdline[i++];
                *cp = 0;
                sscanf(hStr, "%hu:%hu:%hu", &EZ.wHour, &EZ.wMinute, &EZ.wSecond);
                break;

            case 'S': // Spanne
            case 's':
            {
                int p,z1,z2;
                i++;
                if (szCmdline[i] == '=')
                    i++;
                if (szCmdline[i] == ':')
                    i++;
                cp = hStr;
                while ((szCmdline[i] != ' ') && (szCmdline[i] != '\0'))
                    *(cp++) = szCmdline[i++];
                *cp = 0;
                p = sscanf(hStr, "%d:%d", &z1, &z2);
                switch(p)
                {
                    case 2:
                        p = z1*60+z2;
                        break;
                    case 1:
                        p = z1;
                        break;
                    default:
                        p = 0;
                        break;
                }
                GetLocalTime(&EZ);
                EZ.wSecond = 0;
                AddTime(p);
                break;
            }

            case 'N':
            case 'n':
                SetNextEvent();
                AktToolTip();
                SaveRect();
                break;

            case '/': // Spanne
            case '-':
                //i++;
                break;

            default:
                //i++;
                break;
        }
        i++;
    }
}

char* GetVersionString(char *szVersion)
{
    HMODULE hModule;
    char fname[201];
    int vis;
    void *vi;
    void *version;
    unsigned iv = sizeof(version);

    hModule = (HMODULE)GetModuleHandle (NULL);
    GetModuleFileName (hModule, fname, 200);
    vis = GetFileVersionInfoSize (fname, NULL);
    if (vis)
    {
        vi = malloc (vis);
        GetFileVersionInfo (fname, 0, vis, vi);
        VerQueryValue (vi, "\\StringFileInfo\\0C0704B0\\ProductVersion", &version, &iv);
    }
    sprintf (szVersion, "%s", (char *)version);
    return szVersion;
}
int GetMyVersion(char *szVersion)
{
    HMODULE hModule;
    char fname[201], sFormat[201];
    int ret;
    int vis;
    void *vi;
    void * version;
    void * copyright;
    unsigned iv = sizeof(version);
    unsigned ic = sizeof(copyright);
    char tag[3], monat[5], jahr[5], datum[15];

    sscanf (__DATE__, "%3s %2s %4s", monat, tag, jahr);
    sprintf (datum, "%s. %s %s", tag, monat, jahr);

    hModule = (HMODULE)GetModuleHandle (NULL);
    LoadString (hModule, IDS_ABOUT_FORM, sFormat, 200);

    GetModuleFileName (hModule, fname, 200);
    vis = GetFileVersionInfoSize (fname, NULL);
    if (vis)
    {
        vi = malloc (vis);
        GetFileVersionInfo (fname, 0, vis, vi);
        VerQueryValue (vi, "\\StringFileInfo\\0C0704B0\\ProductVersion", &version, &iv);
        VerQueryValue (vi, "\\StringFileInfo\\0C0704B0\\LegalCopyRight", &copyright, &ic);

#if defined (__clang__)
        sprintf (szVersion, sFormat, "Clang", __clang_major__, __clang_minor__, __clang_patchlevel__, (char *)version, datum, __TIME__, (char *)copyright);
#elif defined (__TINYC__)
        sprintf (szVersion, sFormat, "TinyCC", 0, __TINYC__ / 100, __TINYC__ % 100, (char *)version, datum, __TIME__, (char *)copyright);
#elif defined (__GNUC__)
        sprintf (szVersion, sFormat, "GCC", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__, (char *)version, datum, __TIME__, (char *)copyright);
#elif defined (__POCC__)
        sprintf (szVersion, sFormat, "pocc", __POCC__ / 100, __POCC__ % 100, 0, (char *) version, datum, __TIME__, (char *) copyright);
#elif defined (__ORANGEC__)
        sprintf (szVersion, sFormat, "Orange C/C++", __ORANGEC__ / 100, __ORANGEC__ % 100, 0, (char *) version, datum, (char *) copyright);
#elif defined (_MSC_VER)
        sprintf (szVersion, sFormat, "MSVC", _MSC_VER / 100, (_MSC_VER / 10) % 10, _MSC_VER % 10, (char *)version, datum, __TIME__, (char *)copyright);
#else
        sprintf (szVersion, sFormat, 9, 9, 9, (char *)version, datum, __TIME__, (char *)copyright);
#endif // __GNUC__

        free (vi);
        ret = 0;
    }
    else
    {
        ret = -1;
    }
    return ret;
}


// zur Endzeit EZ 'diff'-Minuten addieren
void AddTime(int diff)
{
    EZ.wMinute += (short)diff;
    if (EZ.wMinute >= 60)
    {
        EZ.wHour += EZ.wMinute/60;
        EZ.wMinute %= 60;
        if (EZ.wHour >= 24)
        {
            EZ.wHour %= 24;
        }
    }
    erreicht = 0;
}

//****************************************************************************
//  SetNextEvent
//****************************************************************************
void SetNextEvent(void)
{
    SYSTEMTIME st;
//    int akt;
//    int evt;
    int dif;
    int min = (167*60+59)*60+59;

    GetLocalTime(&st);
//    akt = (st.wHour*60+st.wMinute)*60+st.wSecond;

    for(int i=0; i<10; i++)
    {
        ereignis *e = &ereignisse[i];

        if (strlen(e->grund) > 0)
        {
            erreicht = 0;
//            evt = (24*60+00)*60+00;
//            if (evt < akt)
//            {
//                evt += (e->std*60+e->min)*60+e->sec;
//            }
//            dif = evt - akt;
            dif = TimeToEvent(wota[st.wDayOfWeek],st.wHour,st.wMinute,st.wSecond,e);
            if (dif < min)
            {
                min = dif;
                EZ.wHour = e->std;
                EZ.wMinute = e->min;
                EZ.wSecond = e->sec;
                strcpy(alarmgrund, e->grund);
                strcpy(wochentag, e->wt);
            }
        }
    }
}

//****************************************************************************
//  SetNextEvent
//****************************************************************************
void AktEvent2Liste(void)
{
    int i;

    for(i=0; i<10; i++)
    {
        if(strlen(ereignisse[i].grund) == 0)
        {
            ereignisse[i].std = (BYTE)EZ.wHour;
            ereignisse[i].min = (BYTE)EZ.wMinute;
            ereignisse[i].sec = (BYTE)EZ.wSecond;
            strcpy(ereignisse[i].grund, alarmgrund);
            strcpy(ereignisse[i].wt, wochentag);
            return;
        }
    }
    MessageBox(uhren[0].hWnd,"kein Platz frei!","Ereignis in Liste eintragen",MB_ICONERROR);
}

//****************************************************************************
//  trim
//****************************************************************************
char *trim(char *string)
{
    int stPos,endPos;
    int len = strlen(string);
    for(endPos = len - 1;endPos >= 0 && (string[endPos] == ' '||string[endPos] == '\t'||string[endPos] == '\n');--endPos)
        ;
    for(stPos = 0;stPos < endPos && (string[stPos] == ' '||string[stPos] == '\t');++stPos)
        ;
    char *trimmedStr = (char *)malloc((len+1) * sizeof(char));
    strncpy(trimmedStr, string + stPos, endPos + 1);
    trimmedStr[endPos+1] = 0;
    return trimmedStr;
}

//****************************************************************************
//  dotrim
//****************************************************************************
char *dotrim(char *string)
{
    char *hStr = trim(string);
    strcpy(string, hStr);
    free(hStr);
    return string;
}

//****************************************************************************
//  AktToolTip - Tooltip aktuallisieren
//****************************************************************************
void AktToolTip(void)
{
    if (toolTip.cbSize == 0)
    {
        toolTip.cbSize = sizeof(TOOLINFO);
        toolTip.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
    }

    SendMessage(uhren[0].hToolTip, TTM_DELTOOL, 0, (LPARAM)(&toolTip));
    SendMessage(uhren[1].hToolTip, TTM_DELTOOL, 0, (LPARAM)(&toolTip));
    SendMessage(uhren[2].hToolTip, TTM_DELTOOL, 0, (LPARAM)(&toolTip));

    DestroyWindow(uhren[0].hToolTip);
    DestroyWindow(uhren[1].hToolTip);
    DestroyWindow(uhren[2].hToolTip);

    //toolTip.uId = (UINT_PTR)(hwndDlg);
    toolTip.lpszText = alarmgrund;

    toolTip.uId = (UINT_PTR)uhren[0].hWnd;
    toolTip.hwnd = uhren[0].hWnd;
    uhren[0].hToolTip = CreateWindowEx(0, TOOLTIPS_CLASS, NULL, WS_POPUP | WS_BORDER | TTS_ALWAYSTIP,
                                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                       toolTip.hwnd, NULL, ghInstance, NULL);
    SendMessage(uhren[0].hToolTip, TTM_ADDTOOL, 0, (LPARAM)(&toolTip));

    toolTip.uId = (UINT_PTR)uhren[1].hWnd;
    toolTip.hwnd = uhren[1].hWnd;
    uhren[1].hToolTip = CreateWindowEx(0, TOOLTIPS_CLASS, NULL, WS_POPUP | WS_BORDER | TTS_ALWAYSTIP,
                                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                       toolTip.hwnd, NULL, ghInstance, NULL);
    SendMessage(uhren[1].hToolTip, TTM_ADDTOOL, 0, (LPARAM)(&toolTip));

    toolTip.uId = (UINT_PTR)uhren[2].hWnd;
    toolTip.hwnd = uhren[2].hWnd;
    uhren[2].hToolTip = CreateWindowEx(0, TOOLTIPS_CLASS, NULL, WS_POPUP | WS_BORDER | TTS_ALWAYSTIP,
                                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                       toolTip.hwnd, NULL, ghInstance, NULL);
    SendMessage(uhren[2].hToolTip, TTM_ADDTOOL, 0, (LPARAM)(&toolTip));

    UpdateWindow(uhren[0].hWnd);
    UpdateWindow(uhren[1].hWnd);
    UpdateWindow(uhren[2].hWnd);

    // MessageBox(NULL,alarmgrund,"neuer Alarm",MB_OK);
}

//****************************************************************************
//  SortList
//****************************************************************************
void SortList(void)
{
    SYSTEMTIME tm;
    int times[10] = {0};
    ereignis * e1, *e2;
    int v1, v2;
    int ok = 0;
    int tausch;

    GetLocalTime(&tm);
    for (int i=0; i < 10; i++)
    {
        times[i] = TimeToEvent(wota[tm.wDayOfWeek],tm.wHour,tm.wMinute,tm.wSecond,&ereignisse[i]);
    }

    while(!ok)
    {
        ok = 1;
        for(int i = 0; i < 9; i++)
        {
            e1 = &ereignisse[i];
            e2 = &ereignisse[i + 1];
            tausch = 0;
            if(strlen(e1->grund) == 0)
            {
                if(strlen(e2->grund) > 0)
                {
                    tausch = 1;
                }
            }
            else
            {
                if (strlen(e2->grund) > 0)
                {
                    //v1 = (e1->std * 100 + e1->min) * 100 + e1->sec;
                    //v2 = (e2->std * 100 + e2->min) * 100 + e2->sec;
                    v1 = times[i+0];
                    v2 = times[i+1];
                    if(v2 < v1)
                    {
                        tausch = 1;
                    }
                }
            }
            if(tausch == 1)
            {
                ereignis he;
                int hi;
                he = *e1;
                *e1 = *e2;
                *e2 = he;

                hi = times[i+0];
                times[i+0] = times[i+1];
                times[i+1] = hi;

                ok = 0;
            }
        }
    }
}

//****************************************************************************
//  FillBitmap
//****************************************************************************
static void FillBitmap(HDC mdc, HBITMAP hBitmap, LONG x, LONG y, COLORREF Color)
{
    HBITMAP hRetBmp;
    HBRUSH hBrush;
    RECT fRect;

    hRetBmp = SelectObject(mdc, hBitmap);
    /* Pinssel und Rechteck ermitteln */
    hBrush = CreateSolidBrush(Color);
    fRect.top = fRect.left = x;
    fRect.right = fRect.bottom = y;
    /* Farbe setzen */
    FillRect(mdc, &fRect, hBrush);
    DeleteObject(hBrush);
    SelectObject(mdc, hRetBmp);
}

//****************************************************************************
//  ConvLinePoint
//****************************************************************************
static void ConvLinePoint(const int hmx, const int hmy, POINT *pt, int flag)
{
    switch (flag)
    {
        case 0: /* 0 bis 14 */
            pt->x = hmx;
            pt->y = hmy;
            break;
        case 1: /* 15 bis 29 */
            pt->x = IMAGESIZE - hmy;
            pt->y = hmx;
            break;
        case 2: /* 30 bis 44 */
            pt->x = IMAGESIZE - hmx;
            pt->y = IMAGESIZE - hmy;
            break;
        case 3: /* 45 bis 59 */
            pt->x = hmy;
            pt->y = IMAGESIZE - hmx;
            break;
    }
}

//****************************************************************************
//  ConvBigLinePoint
//****************************************************************************
static void ConvBigLinePoint(const int hmx, const int hmy, POINT *pt, int flag)
{
    switch (flag)
    {
        case 0: /* 0 bis 14 */
            pt->x = hmx;
            pt->y = hmy;
            break;
        case 1: /* 15 bis 29 */
            pt->x = BIGIMAGESIZE - hmy;
            pt->y = hmx;
            break;
        case 2: /* 30 bis 44 */
            pt->x = BIGIMAGESIZE - hmx;
            pt->y = BIGIMAGESIZE - hmy;
            break;
        case 3: /* 45 bis 59 */
            pt->x = hmy;
            pt->y = BIGIMAGESIZE - hmx;
            break;
    }
}

//****************************************************************************
//  CreateTimeIcon
//****************************************************************************
static HICON CreateTimeIcon(HWND hWnd)
{
    HDC hdc, mdc;
    HIMAGELIST IconList, mIconList, tIconList;
    HICON hIcon;
    HBITMAP hBitmap;
    HBITMAP hMaskBitmap;
    HBITMAP hRetBmp;
    HPEN hPen;

    POINT pt[2];
    SYSTEMTIME systim;

    int index, flag;
    static int gMinute = -1;
    static int gWStd = -1, gWMin = -1;

    // Tabelle für Stundenzeiger
    const static int hy[] = {  4,  4,  5,  7,  8, 11, 13, 16,};
    const static int hx[] = { 20, 23, 26, 29, 31, 33, 35, 36,};
    // Tabelle für Minutenzeiger
    const static int my[] = {  0,  0,  0,  1,  2,  3,  4,  5,  7,  8, 10, 12, 14, 16, 18,};
    const static int mx[] = { 20, 22, 24, 26, 28, 30, 32, 33, 35, 36, 37, 38, 39, 40, 40,};

    /* Zeit ermitteln und auf Änderung prüfen */
    GetLocalTime(&systim);
    if (systim.wMinute == gMinute)
    {
        if ((gWStd == EZ.wHour) && (gWMin == EZ.wMinute))
        {
            return NULL;
        }
        else
        {
            gWStd = EZ.wHour;
            gWMin = EZ.wMinute;
        }
    }
    gMinute = systim.wMinute;

    // S T U N D E N - Z e i g e r
    hdc = GetDC(hWnd);
    mdc = CreateCompatibleDC(hdc);

    /* Bitmap für Vordergrund erzeugen */
    hBitmap = CreateCompatibleBitmap(hdc, ICONSIZE, ICONSIZE);
    FillBitmap(mdc, hBitmap, 0, ICONSIZE, (systim.wHour>=12)?STUNDE_COLOR_PM:STUNDE_COLOR_AM);

    /* Bitmap für Maske erzeugen */
    hMaskBitmap = CreateCompatibleBitmap(hdc, ICONSIZE, ICONSIZE);
    FillBitmap(mdc, hMaskBitmap, 0, ICONSIZE, MASK_COLOR);
    ReleaseDC(hWnd, hdc);
    hRetBmp = SelectObject(mdc, hMaskBitmap);

    pt[0].x = pt[0].y = IMAGESIZE / 2 + 1;
    /* Stundenzeiger zeichnen */
    index = ((systim.wHour % 12) * 5) + (systim.wMinute / 15);
    flag = index / 15;
    index %= 15;
    index = (((index * 10) / 2) + 5) / 10;
    ConvLinePoint(hx[index], hy[index], &pt[1], flag);
    hPen = CreatePen(PS_SOLID, 3, (systim.wHour>=12)?STUNDE_COLOR_PM:STUNDE_COLOR_AM);
    SelectObject(mdc, hPen);
    Polyline(mdc, pt, sizeof(pt) / sizeof(POINT));
    DeleteObject(hPen);

    /* Icon zusammen setzen */
    IconList = ImageList_Create(ICONSIZE, ICONSIZE, ILC_COLOR8 | ILC_MASK, 4, 5);
    ImageList_AddIcon(IconList, hBackIcon);

    /* GDI  */
    SelectObject(mdc, hRetBmp);
    DeleteDC(mdc);

    /* Zeit Icon zusammen setzen */
    ImageList_Add(IconList, hBitmap, hMaskBitmap);
    DeleteObject(hBitmap);
    DeleteObject(hMaskBitmap);

    // M I N U T E N - Z e i g e r

    hdc = GetDC(hWnd);
    mdc = CreateCompatibleDC(hdc);
    /* Bitmap für Vordergrund erzeugen */
    hBitmap = CreateCompatibleBitmap(hdc, ICONSIZE, ICONSIZE);
    FillBitmap(mdc, hBitmap, 0, ICONSIZE, MINUTE_COLOR);

    /* Bitmap für Maske erzeugen */
    hMaskBitmap = CreateCompatibleBitmap(hdc, ICONSIZE, ICONSIZE);
    FillBitmap(mdc, hMaskBitmap, 0, ICONSIZE, MASK_COLOR);
    ReleaseDC(hWnd, hdc);
    hRetBmp = SelectObject(mdc, hMaskBitmap);

    /* Minutenzeiger zeichnen */
    index = systim.wMinute % 15;
    flag = systim.wMinute / 15;
    ConvLinePoint(mx[index], my[index], &pt[1], flag);
    hPen = CreatePen(PS_SOLID, 2, MINUTE_COLOR);
    SelectObject(mdc, hPen);
    Polyline(mdc, pt, sizeof(pt) / sizeof(POINT));
    DeleteObject(hPen);

    /* Zeit Icon zusammen setzen */
    SelectObject(mdc, hRetBmp);
    DeleteDC(mdc);
    ImageList_Add(IconList, hBitmap, hMaskBitmap);
    DeleteObject(hBitmap);
    DeleteObject(hMaskBitmap);

    // W E C K E R - Zeiger
    hdc = GetDC(hWnd);
    mdc = CreateCompatibleDC(hdc);

    /* Bitmap für Vordergrund erzeugen */
    hBitmap = CreateCompatibleBitmap(hdc, ICONSIZE, ICONSIZE);
    FillBitmap(mdc, hBitmap, 0, ICONSIZE, (EZ.wHour>=12)?WECKER_COLOR_PM:WECKER_COLOR_AM);

    /* Bitmap für Maske erzeugen */
    hMaskBitmap = CreateCompatibleBitmap(hdc, ICONSIZE, ICONSIZE);
    FillBitmap(mdc, hMaskBitmap, 0, ICONSIZE, MASK_COLOR);
    ReleaseDC(hWnd, hdc);
    hRetBmp = SelectObject(mdc, hMaskBitmap);

    /* Stundenzeiger zeichnen */
    index = ((EZ.wHour % 12) * 5) + (EZ.wMinute / 15);
    flag = index / 15;
    index %= 15;
    index = (((index * 10) / 2) + 5) / 10;
    ConvLinePoint(hx[index], hy[index], &pt[1], flag);
    hPen = CreatePen(PS_SOLID, 2, (EZ.wHour>=12)?WECKER_COLOR_PM:WECKER_COLOR_AM);
    SelectObject(mdc, hPen);
    Polyline(mdc, pt, sizeof(pt) / sizeof(POINT));
    DeleteObject(hPen);

    /* Maske setzen */
    FillBitmap(mdc, hMaskBitmap, IMAGESIZE / 2, IMAGESIZE / 2 + 1, MASK_COLOR);

    /* Wecker Icon zusammen setzen */
    SelectObject(mdc, hRetBmp);
    DeleteDC(mdc);
    ImageList_Add(IconList, hBitmap, hMaskBitmap);
    DeleteObject(hBitmap);
    DeleteObject(hMaskBitmap);

    // "Mergen" der Icons
    mIconList = ImageList_Merge(IconList, 0, IconList, 1, 0, 0);  // Originalicon + Stundenzeiger
    tIconList = ImageList_Merge(mIconList, 0, IconList, 2, 0, 0);  // + Minutenzeiger
    ImageList_Destroy(mIconList);
    mIconList = ImageList_Merge(tIconList, 0, IconList, 3, 0, 0);  // Wecker
    ImageList_Destroy(tIconList);

    hIcon = ImageList_GetIcon(mIconList, 0, ILD_NORMAL);
    ImageList_Destroy(mIconList);
    ImageList_Destroy(IconList);

    return hIcon;
}

//****************************************************************************
//  CreateBigTimeIcon
//****************************************************************************
static HICON CreateBigTimeIcon(HWND hWnd)
{
    HDC hdc, mdc;
    HIMAGELIST IconList, mIconList, tIconList;
    HICON hIcon;
    HBITMAP hBitmap;
    HBITMAP hMaskBitmap;
    HBITMAP hRetBmp;
    HPEN hPen;

    POINT pt[2];
    SYSTEMTIME systim;

    int index, flag;
    static int gWStd = -1, gWMin = -1, gSekunde = -1;

    // Tabelle für Stundenzeiger
    const static int hy[] = { 10, 10, 11, 12, 13, 15, 17, 20, 23, 26, 29, 33, 36, 40, 44,};
    const static int hx[] = { 48, 52, 56, 60, 63, 67, 70, 73, 76, 79, 81, 83, 84, 85, 86,};
    // Tabelle für Minutenzeiger
    const static int my[] = {  0,  0,  1,  2,  4,  6,  9, 12, 16, 20, 24, 28, 33, 38, 43,};
    const static int mx[] = { 48, 53, 58, 63, 68, 72, 76, 80, 84, 87, 90, 92, 94, 95, 96,};

    /* Zeit ermitteln und auf Änderung prüfen */
    GetLocalTime(&systim);
    if (systim.wSecond == gSekunde)
    {
        if ((gWStd == EZ.wHour) && (gWMin == EZ.wMinute))
        {
            return NULL;
        }
        else
        {
            gWStd = EZ.wHour;
            gWMin = EZ.wMinute;
        }
    }
    gSekunde = systim.wSecond;

    pt[0].x = pt[0].y = BIGIMAGESIZE / 2;

    // W E C K E R - Zeiger
    hdc = GetDC(hWnd);
    mdc = CreateCompatibleDC(hdc);

    /* Bitmap für Vordergrund erzeugen */
    hBitmap = CreateCompatibleBitmap(hdc, BIGICONSIZE, BIGICONSIZE);
    FillBitmap(mdc, hBitmap, 0, BIGICONSIZE, (EZ.wHour>=12)?WECKER_COLOR_PM:WECKER_COLOR_AM);

    /* Bitmap für Maske erzeugen */
    hMaskBitmap = CreateCompatibleBitmap(hdc, BIGICONSIZE, BIGICONSIZE);
    FillBitmap(mdc, hMaskBitmap, 0, BIGICONSIZE, MASK_COLOR);
    ReleaseDC(hWnd, hdc);
    hRetBmp = SelectObject(mdc, hMaskBitmap);

    /* Stundenzeiger zeichnen */
    index = ((EZ.wHour % 12) * 5) + (EZ.wMinute / 15);
    flag = index / 15;
    index %= 15;
    //index = (((index * 10) / 2) + 5) / 10;
    ConvBigLinePoint(hx[index], hy[index], &pt[1], flag);
    hPen = CreatePen(PS_SOLID, 4, (EZ.wHour>=12)?WECKER_COLOR_PM:WECKER_COLOR_AM);
    SelectObject(mdc, hPen);
    Polyline(mdc, pt, sizeof(pt) / sizeof(POINT));
    DeleteObject(hPen);

    /* Maske setzen */
    FillBitmap(mdc, hMaskBitmap, BIGIMAGESIZE / 2, BIGIMAGESIZE / 2 + 1, MASK_COLOR);

    /* Wecker Icon zusammen setzen */
    SelectObject(mdc, hRetBmp);
    DeleteDC(mdc);
    IconList = ImageList_Create(BIGICONSIZE, BIGICONSIZE, ILC_COLOR8 | ILC_MASK, 4, 5);

    ImageList_AddIcon(IconList, hBigIcon);

    SelectObject(mdc, hRetBmp);
    DeleteDC(mdc);

    ImageList_Add(IconList, hBitmap, hMaskBitmap);
    DeleteObject(hBitmap);
    DeleteObject(hMaskBitmap);

    //hIcon = ImageList_GetIcon(mIconList, 0, ILD_NORMAL);
    //ImageList_Destroy(mIconList);
    //ImageList_Destroy(IconList);

    // S T U N D E N - Z e i g e r
    hdc = GetDC(hWnd);
    mdc = CreateCompatibleDC(hdc);

    /* Bitmap für Vordergrund erzeugen */
    hBitmap = CreateCompatibleBitmap(hdc, BIGICONSIZE, BIGICONSIZE);
    FillBitmap(mdc, hBitmap, 0, BIGICONSIZE, (systim.wHour>=12)?STUNDE_COLOR_PM:STUNDE_COLOR_AM);

    /* Bitmap für Maske erzeugen */
    hMaskBitmap = CreateCompatibleBitmap(hdc, BIGICONSIZE, BIGICONSIZE);
    FillBitmap(mdc, hMaskBitmap, 0, BIGICONSIZE, MASK_COLOR);
    ReleaseDC(hWnd, hdc);
    hRetBmp = SelectObject(mdc, hMaskBitmap);


    /* Stundenzeiger zeichnen */
    index = ((systim.wHour % 12) * 5) + (systim.wMinute / 15);
    flag = index / 15;
    index %= 15;
    //index = (((index * 10) / 2) + 5) / 10;
    ConvBigLinePoint(hx[index], hy[index], &pt[1], flag);

    hPen = CreatePen(PS_SOLID, 3, (systim.wHour>=12)?STUNDE_COLOR_PM:STUNDE_COLOR_AM);
    SelectObject(mdc, hPen);
    Polyline(mdc, pt, sizeof(pt) / sizeof(POINT));
    DeleteObject(hPen);

    /* GDI  */
    SelectObject(mdc, hRetBmp);
    DeleteDC(mdc);

    /* Zeit Icon zusammen setzen */
    ImageList_Add(IconList, hBitmap, hMaskBitmap);
    DeleteObject(hBitmap);
    DeleteObject(hMaskBitmap);

    // M I N U T E N - Z e i g e r

    hdc = GetDC(hWnd);
    mdc = CreateCompatibleDC(hdc);
    /* Bitmap für Vordergrund erzeugen */
    hBitmap = CreateCompatibleBitmap(hdc, BIGICONSIZE, BIGICONSIZE);
    FillBitmap(mdc, hBitmap, 0, BIGICONSIZE, MINUTE_COLOR);

    /* Bitmap für Maske erzeugen */
    hMaskBitmap = CreateCompatibleBitmap(hdc, BIGICONSIZE, BIGICONSIZE);
    FillBitmap(mdc, hMaskBitmap, 0, BIGICONSIZE, MASK_COLOR);
    ReleaseDC(hWnd, hdc);
    hRetBmp = SelectObject(mdc, hMaskBitmap);

    /* Minutenzeiger zeichnen */
    index = systim.wMinute % 15;
    flag = systim.wMinute / 15;
    ConvBigLinePoint(mx[index], my[index], &pt[1], flag);

    hPen = CreatePen(PS_SOLID, 2, MINUTE_COLOR);
    SelectObject(mdc, hPen);
    Polyline(mdc, pt, sizeof(pt) / sizeof(POINT));
    DeleteObject(hPen);

    /* Zeit Icon zusammen setzen */
    SelectObject(mdc, hRetBmp);
    DeleteDC(mdc);
    ImageList_Add(IconList, hBitmap, hMaskBitmap);
    DeleteObject(hBitmap);
    DeleteObject(hMaskBitmap);

    // S E K U N D E N - Z e i g e r
    hdc = GetDC(hWnd);
    mdc = CreateCompatibleDC(hdc);

    /* Bitmap für Vordergrund erzeugen */
    hBitmap = CreateCompatibleBitmap(hdc, BIGICONSIZE, BIGICONSIZE);
    FillBitmap(mdc, hBitmap, 0, BIGICONSIZE, SEKUNDE_COLOR);

    /* Bitmap für Maske erzeugen */
    hMaskBitmap = CreateCompatibleBitmap(hdc, BIGICONSIZE, BIGICONSIZE);
    FillBitmap(mdc, hMaskBitmap, 0, BIGICONSIZE, MASK_COLOR);
    ReleaseDC(hWnd, hdc);
    hRetBmp = SelectObject(mdc, hMaskBitmap);

    /* Sekundenzeiger zeichnen */
    index = systim.wSecond % 15;
    flag = systim.wSecond / 15;
    ConvBigLinePoint(mx[index], my[index], &pt[1], flag);
    //char hStr[200];
    //sprintf(hStr,"index:%2d flag:%d mx/y:%2d,%2d pt:%2d,%2d\n",index,flag,mx[index], my[index],pt[1].x,pt[1].y);
    //OutputDebugString(hStr);
    hPen = CreatePen(PS_SOLID, 1, SEKUNDE_COLOR);
    SelectObject(mdc, hPen);
    Polyline(mdc, pt, sizeof(pt) / sizeof(POINT));
    DeleteObject(hPen);

    /* Maske setzen */
    FillBitmap(mdc, hMaskBitmap, BIGIMAGESIZE / 2, BIGIMAGESIZE / 2, MASK_COLOR);

    /* Sekunden Icon zusammen setzen */
    SelectObject(mdc, hRetBmp);
    DeleteDC(mdc);
    ImageList_Add(IconList, hBitmap, hMaskBitmap);
    DeleteObject(hBitmap);
    DeleteObject(hMaskBitmap);

    // "Mergen" der Icons
    mIconList = ImageList_Merge(IconList, 0, IconList, 1, 0, 0);  // Originalicon + Stundenzeiger
    tIconList = ImageList_Merge(mIconList, 0, IconList, 2, 0, 0);  // + Minutenzeiger
    ImageList_Destroy(mIconList);
    mIconList = ImageList_Merge(tIconList, 0, IconList, 3, 0, 0);  // Wecker
    ImageList_Destroy(tIconList);
    tIconList = ImageList_Merge(mIconList, 0, IconList, 4, 0, 0);  // + Minutenzeiger
    ImageList_Destroy(mIconList);

    hIcon = ImageList_GetIcon(tIconList, 0, ILD_NORMAL);
    ImageList_Destroy(tIconList);
    ImageList_Destroy(IconList);

    return hIcon;
}

//****************************************************************************
// Setzen der Farben                                                        **
//****************************************************************************
void AktOutput(HWND hwndDlg)
{
    SYSTEMTIME ST;
    LPSYSTEMTIME lpST = &ST;
    char hStr[50];
    static int tag = -1;
    static int ez = -1;
    int restZeit;
    ereignis e;

    GetLocalTime(lpST);
    sprintf(hStr, "%02d:%02d:%02d", lpST->wHour, lpST->wMinute, lpST->wSecond);
    SetDlgItemText(hwndDlg, IDD_UHRZEIT, hStr);

//    CalcRestZeit(ST, EZ, &RZ);
    e.std = (char)EZ.wHour;
    e.min = (char)EZ.wMinute;
    e.sec = (char)EZ.wSecond;
    strcpy(e.wt, wochentag);//BookMark [{AktOutput-wota}]
    restZeit = TimeToEvent(wota[ST.wDayOfWeek],ST.wHour,ST.wMinute,ST.wSecond, &e);
    RZ.wHour = (short)(restZeit / 3600);
    RZ.wMinute = (short)(restZeit / 60 - RZ.wHour * 60);
    RZ.wSecond = restZeit % 60;

    if (ST.wDay != tag)
    {
        sprintf(hStr, "%2s: %02d.%02d.%04d", wota[ST.wDayOfWeek], ST.wDay, ST.wMonth, ST.wYear);
        SendMessage(uhren[0].hWnd, WM_SETTEXT, 0, (size_t)hStr);
        SendMessage(uhren[1].hWnd, WM_SETTEXT, 0, (size_t)hStr);
        SendMessage(uhren[2].hWnd, WM_SETTEXT, 0, (size_t)hStr);
        tag = ST.wDay;
    }

    if (ez != (((EZ.wHour << 6) + EZ.wMinute) << 6) + EZ.wSecond)
    {
        sprintf(hStr, "%02d:%02d:%02d .", EZ.wHour, EZ.wMinute, EZ.wSecond);
        //SetDlgItemText(hwndDlg, IDD_ENDZEIT, hStr);
        SetDlgItemText(uhren[0].hWnd, IDD_ENDZEIT, hStr);
        SetDlgItemText(uhren[1].hWnd, IDD_ENDZEIT, hStr);
        SetDlgItemText(uhren[2].hWnd, IDD_ENDZEIT, hStr);
        ez = (((EZ.wHour << 6) + EZ.wMinute) << 6) + EZ.wSecond;
    }
    sprintf(hStr, "%03d:%02d:%02d .", RZ.wHour, RZ.wMinute, RZ.wSecond);
    if (hStr[0] == '0') hStr[0] = ' ';
    SetDlgItemText(hwndDlg, IDD_RESTZEIT, hStr);

    if (RZ.wHour == 0 && RZ.wMinute == 0 && RZ.wSecond == 0)
    {
        if (AlarmDlg == 0)
        {
            DialogBox(NULL, MAKEINTRESOURCE(DLG_ALARM), hwndDlg, (DLGPROC)DlgProcAlarm);
        }
    }
}

/****************************************************************************
 *
 *     FUNCTION: SetColor
 *
 *     PURPOSE:  Set the colors used to paint controls in OnCtlColor....
 *
 *     PARAMS:   COLORREF TxtColr - Desired text color
 *               COLORREF BkColr - Desired back color
 *               HDC hdc - Handle of a device context
 *
 *     RETURNS:  HBRUSH - A reusable brush object
 *
 * History:
 *                August '07 - Created
 *
\****************************************************************************/

HBRUSH SetBkfColor(COLORREF TxtColr, COLORREF BkColr, HDC hdc)
{
    static HBRUSH ReUsableBrush;
    COLORREF tc, bc;

    if (RZ.wHour > 11)
    {
        tc = TxtColr-0x7f7f7f;
        bc = BkColr+0x7f7f7f;
    }
    else
    {
        tc = TxtColr;
        bc = BkColr;
    }
    DeleteObject(ReUsableBrush);
    ReUsableBrush = CreateSolidBrush(bc);
    SetTextColor(hdc, tc);
    SetBkColor(hdc, bc);
    return ReUsableBrush;
}

//****************************************************************************
// Setzen der Farben                                                        **
//****************************************************************************
void SetColors(HWND hwndCtl, HDC wParam)
{
    static COLORREF old_back = 0;
    int id;
    int delta;
    int abstand = 12*60;
    int tx_r,tx_g,tx_b;
    int bg_r,bg_g,bg_b;

    id = GetWindowLong(hwndCtl, GWL_ID);

    if (id == IDD_RESTZEIT)
    {
        delta = (RZ.wHour * 60 + RZ.wMinute)%abstand;
        // abstand = (DZ.wHour * 60 + DZ.wMinute);
        if (0 == abstand)
            abstand = 60;  // Korrektur bei Abstand 0

        if (erreicht)
        {
            // grün
            bg_r = (127 * (abstand - delta)) / abstand;
            bg_g = ( 15 * (abstand - delta)) / abstand + 112;
            bg_b = 0;
        }
        else
        {
            // rot
            // bg_r = ( 15 * (abstand - delta)) / abstand + 112;
            bg_r = (127 * (          delta)) / abstand;
            bg_g = 0;
            bg_b = (127 * (abstand - delta)) / abstand;
        }
        gBackgroundColor = RGB(bg_r, bg_g, bg_b);

        // Schriftfarbe Schwarz/Weiß oder bunt :)
        if (blackwhite)
        {
            if ((bg_r + bg_g + bg_b) >= 384)
            {
                tx_r = tx_g = tx_b = 0;
            }
            else
            {
                tx_r = tx_g = tx_b = 255;
            }
        }
        else
        {
            tx_r = 127 + bg_r % 128;
            tx_g = 127 + bg_g % 128;
            tx_b = 127 + bg_b % 128;
        }

        gForegroundColor = RGB(tx_r, tx_g, tx_b);
        if (gBackgroundColor != old_back)
        {
            old_back = gBackgroundColor;
            SetTextColor(wParam, gBackgroundColor);
            SetBkColor(wParam, gForegroundColor);
            Refresh(uhren[0].hWnd);
            Refresh(uhren[1].hWnd);
            Refresh(uhren[2].hWnd);
        }
    }

    SetBkMode(wParam, OPAQUE);
}

//****************************************************************************
// Speichern des aktuellen Fensters und Endzeit                             **
//****************************************************************************
void SaveRect(void)
{
    FILE * f;
    char hStr[150];
    char wt[3];

    wt[0] = wochentag[0];
    wt[1] = wochentag[1];
    wt[2] = 0;
    f = fopen(IniName, "w");
    if (f != NULL)
    {
        // Alarm speichern
        wt[0]=(wochentag[0]==0  )?'_':wochentag[0];
        wt[0]=(wochentag[0]==' ')?'_':wochentag[0];
        wt[1]=(wochentag[1]==' ')?'_':wochentag[1];
        sprintf(hStr, "%2s-%02d:%02d:%02d\n", wt, EZ.wHour, EZ.wMinute, EZ.wSecond);
        fwrite(hStr, 1, strlen(hStr), f);

        sprintf(hStr, "%s\n", alarmgrund);
        fwrite(hStr, 1, strlen(hStr), f);

        // Positionen speichern
        sprintf(hStr, "%ld,%ld,%ld,%ld\n",
        uhren[0].rWndDlg.left, uhren[0].rWndDlg.top,
        uhren[0].rWndDlg.right, uhren[0].rWndDlg.bottom);
        fwrite(hStr, 1, strlen(hStr), f);
        sprintf(hStr, "%ld,%ld,%ld,%ld\n",
        uhren[1].rWndDlg.left, uhren[1].rWndDlg.top,
        uhren[1].rWndDlg.right, uhren[1].rWndDlg.bottom);
        fwrite(hStr, 1, strlen(hStr), f);
        sprintf(hStr, "%ld,%ld,%ld,%ld\n",
        uhren[2].rWndDlg.left, uhren[2].rWndDlg.top,
        uhren[2].rWndDlg.right, uhren[2].rWndDlg.bottom);
        fwrite(hStr, 1, strlen(hStr), f);

        // Liste speichern
        for (int i=0; i<10; i++)
        {
            ereignis *e = &ereignisse[i];
            wt[0]=(e->wt[0]==' ')?'_':e->wt[0];
            wt[1]=(e->wt[1]==' ')?'_':e->wt[1];
            wt[0]=(e->wt[0]==0  )?'_':e->wt[0];
            fprintf(f, "%2s-%02d:%02d:%02d,%s\n",wt,e->std,e->min,e->sec,trim(e->grund));
        }
        fclose(f);
    }
}

//****************************************************************************
// Berechnen der Restzeit aus der Jetzt- und Endzeit                        **
//****************************************************************************
void CalcRestZeit(SYSTEMTIME J, SYSTEMTIME E, SYSTEMTIME *rz)
{
    unsigned int iJ, iE, iR;

    memset(rz, 0, sizeof(*rz));

    iJ = (J.wHour * 60 + J.wMinute) * 60 + J.wSecond;
    iE = (E.wHour * 60 + E.wMinute) * 60 + E.wSecond;

    if(erreicht)
    {
        if(iJ > iE)
        {
            iR = iJ - iE;
        }
        else
        {
            iR = iJ + 24 * 3600 - iE;
        }
    }
    else
    {
        // nicht erreicht
        if(iJ > iE)
        {
            iR = iE + 24 * 3600 - iJ;
        }
        else
        {
            iR = iE - iJ;
        }
    }

    rz->wSecond = iR % 60;
    rz->wMinute = (iR / 60) % 60;
    rz->wHour = (unsigned short)(iR / 3600) % 24;
}
/****************************************************************************
 *                                                                          *
 * Function: WinMain                                                        *
 *                                                                          *
 * Purpose : Initialize the application.  Register a window class,          *
 *           create and display the main window and enter the               *
 *           message loop.                                                  *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    INITCOMMONCONTROLSEX icc;
    WNDCLASSEX wcx;
    MSG Msg;
    HANDLE hAccelTable = NULL;
    int wHour, wMinute, wSecond;
    char hStr[200];
    RECT r;
    FILE * f;

    ghInstance = hInstance;
    // Namen für ini ermitteln
    GetModuleFileName(NULL, IniName, sizeof(IniName));
    strcpy(&IniName[strlen(IniName) - 3], "ini");

    /* Initialize common controls. Also needed for MANIFEST's */
    /*
     * TODO: set the ICC_???_CLASSES that you need.
     */
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_WIN95_CLASSES /*|ICC_COOL_CLASSES|ICC_DATE_CLASSES|ICC_PAGESCROLLER_CLASS|ICC_USEREX_CLASSES*/ ;
    InitCommonControlsEx(&icc);

    /* Load Rich Edit control support */
    /*
     * TODO: uncomment one of the lines below, if you are using a Rich Edit control.
     */
    // LoadLibrary(_T("riched32.dll"));  // Rich Edit v1.0
    // LoadLibrary(_T("riched20.dll"));  // Rich Edit v2.0, v3.0

    // Ini-Datei lesen und Werte setzen
    f = fopen(IniName, "r");

    if (f != NULL)
    {
        // Endzeit einlesen
        fgets(hStr, 50, f);
        if (4 == sscanf(hStr, "%2s-%d:%d:%d", wochentag, &wHour, &wMinute, &wSecond))
        {
            EZ.wHour = wHour % 24;
            EZ.wMinute = wMinute % 60;
            EZ.wSecond = wSecond % 60;
            wochentag[0]=(wochentag[0]==' ')?'_':wochentag[0];
            wochentag[1]=(wochentag[1]==' ')?'_':wochentag[1];

        }

        // Grund für Alarm lesen
        fgets(alarmgrund, 100, f);
        dotrim(alarmgrund);

        // Rechteck einlesen
        for (int i = 0; i < 3; i++)
        {
            fgets(hStr, 50, f);
            if (4 == sscanf(hStr, "%ld,%ld,%ld,%ld", &r.left, &r.top, &r.right, &r.bottom))
            {
                uhren[i].rWndDlg = r;
            }
        }

        for (int i = 0; i < 10; i++)
        {
            int h,m,s;
            int x;
            ereignis *e = &ereignisse[i];
            fgets(hStr,200,f);
            if (strncmp(hStr,"  ",2) == 0)
            {
                x = sscanf(hStr,"  -%d:%d:%d,",&h,&m,&s);

                e->wt[0] = ' ';
                e->wt[1] = ' ';
                e->wt[2] = 0;
            }
            else
            {
                x = sscanf(hStr,"%2s-%d:%d:%d,",e->wt,&h,&m,&s);
            }
            e->std = (char)h;
            e->min = (char)m;
            e->sec = (char)s;
            strcpy(e->grund,&hStr[12]);
            dotrim(e->grund);
            e->wt[0]=(e->wt[0]=='_')?' ':e->wt[0];
            e->wt[1]=(e->wt[1]=='_')?' ':e->wt[1];
        }

        // Datei schließen
        fclose(f);
    }

    GetParams(lpszCmdLine);

    /* Get system dialog information */
    wcx.cbSize = sizeof(wcx);
    if (!GetClassInfoEx(NULL, MAKEINTRESOURCE(32770), &wcx))
        return 0;

        /* Add our own stuff */
    wcx.hInstance = hInstance;
    wcx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_ICO_MAIN));
    wcx.lpszClassName = _T("WinUhrWTClass");

    // Tray-Icons laden
    hBackIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDR_ICO_TRAY3), IMAGE_ICON, ICONSIZE, ICONSIZE, 0);
    hBigIcon  = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDR_ICO_TRAY4), IMAGE_ICON, BIGICONSIZE, BIGICONSIZE, 0);

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDACCEL));

    if (!RegisterClassEx(&wcx))
        return 0;

        /* The user interface is a modal dialog box */

        //hWindow  = CreateWindow("myWinUhr2","WinUhr2",0,100,100,1,1,NULL,NULL,hInstance,NULL);
    uhren[0].hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(DLG_MAIN_X), NULL, (DLGPROC)DlgProcMain);
    uhren[1].hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(DLG_MAIN_Y), NULL, (DLGPROC)DlgProcMain);
    uhren[2].hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(DLG_MAIN_Z), NULL, (DLGPROC)DlgProcMain);
    Refresh(uhren[0].hWnd);
    Refresh(uhren[1].hWnd);
    Refresh(uhren[2].hWnd);
    //DialogBox(hInstance, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgProcMain);

    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        if (!TranslateAccelerator(uhren[0].hWnd,hAccelTable,&Msg))
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
    }

    return TRUE;
}

/****************************************************************************
 *                                                                          *
 * Function: MainDlgProc                                                    *
 *                                                                          *
 * Purpose : Process messages for the Main dialog.                          *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

static LRESULT CALLBACK DlgProcMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    char hStr[100];
    SYSTEMTIME Jetzt;
    POINT pt;
    static int done = 0;
    static int sU = 0;
    int selUhr = -1;
    int i;

    memset(hStr, 0, 100);

    for (i = 0;i < 3;i++)
    {
        if (uhren[i].hWnd == hwndDlg)
        {
            selUhr = i;
            break;
        }
    }

    switch (uMsg)
    {
        case WM_INITDIALOG:
            // Timer starten
            SetTimer(hwndDlg, TIMER_UHR , 250, NULL);
            SetTimer(hwndDlg, TIMER_UHRA, 500, NULL);

            // Popup-Menü erzeugen
            if (NULL == hPopupMenu)
            {
                hPopupMenu = CreatePopupMenu();
                AppendMenu(hPopupMenu, MF_STRING, IDM_EDIT, "Eingabe &Endzeit");
                AppendMenu(hPopupMenu, MF_STRING, IDM_LIST, "Bearbeite &Liste");
                AppendMenu(hPopupMenu, MF_STRING, IDM_SORT, "&Sortiere Liste");
                AppendMenu(hPopupMenu, MF_STRING, IDM_NEXT, "&nächstes Ereignis");
                //AppendMenu(hPopupMenu, MF_STRING | MF_CHECKED, IDM_RESTZEIT, "&Restzeit bei Minimiert");
                AppendMenu(hPopupMenu, MF_SEPARATOR, 0, 0);
                AppendMenu(hPopupMenu, MF_STRING, IDM_HIDEX, "&Verstecken B");
                AppendMenu(hPopupMenu, MF_STRING, IDM_HIDEY, "&Verstecken D");
                AppendMenu(hPopupMenu, MF_STRING, IDM_HIDEZ, "&Verstecken A");
                AppendMenu(hPopupMenu, MF_SEPARATOR, 0, 0);
                AppendMenu(hPopupMenu, MF_STRING, IDM_TOPX, "&TopMost B");
                AppendMenu(hPopupMenu, MF_STRING, IDM_TOPY, "&TopMost D");
                AppendMenu(hPopupMenu, MF_STRING, IDM_TOPZ, "&TopMost A");
                AppendMenu(hPopupMenu, MF_SEPARATOR, 0, 0);
                AppendMenu(hPopupMenu, MF_STRING, IDM_NOSOUND, "&kein Sound");
                AppendMenu(hPopupMenu, MF_STRING, IDM_RESTORE, "&Wiederherstellen");
                AppendMenu(hPopupMenu, MF_SEPARATOR, 0, 0);
                AppendMenu(hPopupMenu, MF_STRING, IDM_STATUS, "Stat&us");
                AppendMenu(hPopupMenu, MF_STRING, IDM_INFO, "&Info");
                AppendMenu(hPopupMenu, MF_STRING, IDM_EXIT, "&Ende");
            }

            // System-Menü erzeugen
            if (selUhr == -1)
            {
                selUhr = sU++;
            }
            uhren[selUhr].hSMenu = GetSystemMenu(hwndDlg, FALSE);
            AppendMenu(uhren[selUhr].hSMenu, MF_SEPARATOR, 0, 0);
            AppendMenu(uhren[selUhr].hSMenu, MF_STRING, IDM_STATUS, "Stat&us");
            AppendMenu(uhren[selUhr].hSMenu, MF_STRING, IDM_INFO, "&Info");
            AppendMenu(uhren[selUhr].hSMenu, MF_SEPARATOR, 0, 0);
            AppendMenu(uhren[selUhr].hSMenu, MF_STRING, IDM_EDIT, "Eingabe &Endzeit");
            AppendMenu(uhren[selUhr].hSMenu, MF_STRING, IDM_LIST, "Bearbeite &Liste");
            AppendMenu(uhren[selUhr].hSMenu, MF_STRING, IDM_SORT, "&Sortiere Liste");
            AppendMenu(uhren[selUhr].hSMenu, MF_STRING, IDM_NEXT, "&nächstes Ereignis");
            AppendMenu(uhren[selUhr].hSMenu, MF_SEPARATOR, 0, 0);
            AppendMenu(uhren[selUhr].hSMenu, MF_STRING, IDM_TOP, "&TopMost");
            AppendMenu(uhren[selUhr].hSMenu, MF_STRING, IDM_HIDE, "&Verstecken");
            AppendMenu(uhren[selUhr].hSMenu, MF_STRING, IDM_NOSOUND, "&kein Sound");

            AktToolTip();

            SetColors(hwndDlg, (HDC)wParam);
            SetBkfColor(gForegroundColor, gBackgroundColor, (HDC)wParam);

            // Tray-Icon erzeugen
            if (nid.cbSize == 0)
            {
                nid.cbSize = sizeof(NOTIFYICONDATA);  //Most API Structs require this
                nid.hWnd = hwndDlg;
                nid.uID = IDR_ICO_TRAY3;
                nid.uFlags = NIF_ICON + NIF_MESSAGE + NIF_TIP;  //Flags to set requires fields
                nid.uCallbackMessage = WM_SHELLNOTIFY;  // Message ID sent when the pointer enters Tray icon area
                nid.hIcon = LoadIcon(ghInstance, MAKEINTRESOURCE(IDR_ICO_MAIN));  //Load Icon for tray
                lstrcpy(nid.szTip, "WinUhrWT");  //Tray Icon Tool Tip
                Shell_NotifyIcon(NIM_ADD, &nid);  //Show the Icon
            }

            return TRUE;

        case WM_SHELLNOTIFY:
            //Called when pointer entry tray icon area
            if (wParam == IDR_ICO_TRAY3)
            {
                //Show PopUp menu if right button down
                if (lParam == WM_RBUTTONDOWN)
                {
                    GetCursorPos(&pt);
                    SetForegroundWindow(hwndDlg);
                    TrackPopupMenu(hPopupMenu, TPM_RIGHTALIGN, pt.x, pt.y, 0, hwndDlg, 0);
                    PostMessage(hwndDlg, WM_NULL, 0, 0);
                    return TRUE;
                }
                else if (WM_LBUTTONDBLCLK == lParam)
                {
                    // Restore Window
                    SendMessage(hwndDlg, WM_COMMAND, IDM_RESTORE, 0);
                }
            }
            break;

        case WM_COMMAND:
            switch (GET_WM_COMMAND_ID(wParam, lParam))
            {
                case IDM_EXIT:
                    //SendMessage(hwndDlg, WM_CLOSE, 0, 0);
                    SendMessage(uhren[0].hWnd, WM_CLOSE, 0, 0);
                    SendMessage(uhren[1].hWnd, WM_CLOSE, 0, 0);
                    SendMessage(uhren[2].hWnd, WM_CLOSE, 0, 0);
                    exit(0);
                    return TRUE;

                case IDM_RESTORE:
                    //minimized = 0;
                    ShowWindow(hwndDlg, SW_RESTORE);
                    break;

                case IDM_RESTZEIT:
                    show_rest = !show_rest;
                    if (show_rest)
                    {
                        CheckMenuItem(uhren[selUhr].hSMenu, IDM_RESTZEIT, MF_CHECKED);
                        CheckMenuItem(hPopupMenu, IDM_RESTZEIT, MF_CHECKED);
                    }
                    else
                    {
                        CheckMenuItem(uhren[selUhr].hSMenu, IDM_RESTZEIT, MF_UNCHECKED);
                        CheckMenuItem(hPopupMenu, IDM_RESTZEIT, MF_UNCHECKED);
                    }
                    return TRUE;

                case IDM_EDIT:
                    DialogBox(ghInstance, MAKEINTRESOURCE(DLG_EDIT), hwndDlg, (DLGPROC)DlgProcEdit);
                    AktToolTip();
                    SaveRect();
                    return TRUE;

                case IDM_STATUS:
                    DialogBox(ghInstance, MAKEINTRESOURCE(DLG_STATUS), hwndDlg, (DLGPROC)DlgProcStatus);
                    return TRUE;

                case IDM_INFO:
                    DialogBox(ghInstance, MAKEINTRESOURCE(DLG_INFO), hwndDlg, (DLGPROC)DlgProcInfo);
                    return TRUE;

                case IDM_LIST:
                    DialogBox(ghInstance, MAKEINTRESOURCE(DLG_EVENTLIST), hwndDlg, (DLGPROC)DlgProcList);
                    AktToolTip();
                    SaveRect();
                    return TRUE;

                case IDM_SORT:
                    SortList();
                    SaveRect();
                    return TRUE;

                case IDM_HIDEX:
                    uhren[0].hide = !uhren[0].hide;
                    CheckMenuItem(hPopupMenu, IDM_HIDEX, uhren[0].hide?MF_CHECKED:MF_UNCHECKED);
                    ShowWindow(uhren[0].hWnd, uhren[0].hide?SW_HIDE:SW_SHOW);
                    ShowWindow(uhren[0].hWnd, uhren[0].hide?SW_HIDE:SW_RESTORE);
                    // Restore Window
                    SendMessage(uhren[0].hWnd, WM_COMMAND, IDM_RESTORE, 0);
                    return TRUE;

                case IDM_HIDEY:
                    uhren[1].hide = !uhren[1].hide;
                    CheckMenuItem(hPopupMenu, IDM_HIDEY, uhren[1].hide?MF_CHECKED:MF_UNCHECKED);
                    ShowWindow(uhren[1].hWnd, uhren[1].hide?SW_HIDE:SW_RESTORE);
                    // Restore Window
                    SendMessage(uhren[1].hWnd, WM_COMMAND, IDM_RESTORE, 0);
                    return TRUE;

                case IDM_HIDEZ:
                    uhren[2].hide = !uhren[2].hide;
                    CheckMenuItem(hPopupMenu, IDM_HIDEZ, uhren[2].hide?MF_CHECKED:MF_UNCHECKED);
                    ShowWindow(uhren[2].hWnd, uhren[2].hide?SW_HIDE:SW_MAXIMIZE);
                    // Restore Window
                    SendMessage(uhren[2].hWnd, WM_COMMAND, IDM_RESTORE, 0);
                    return TRUE;

                case IDM_TOPX:
                    uhren[0].top = !uhren[0].top;
                    CheckMenuItem(hPopupMenu, IDM_TOPX, uhren[0].top?MF_CHECKED:MF_UNCHECKED);
                    CheckMenuItem(uhren[0].hSMenu, IDM_TOP, uhren[0].top?MF_CHECKED:MF_UNCHECKED);
                    SetWindowPos(uhren[0].hWnd, uhren[0].top?HWND_TOPMOST:HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                    return TRUE;

                case IDM_TOPY:
                    uhren[1].top = !uhren[1].top;
                    CheckMenuItem(hPopupMenu, IDM_TOPY, uhren[1].top?MF_CHECKED:MF_UNCHECKED);
                    CheckMenuItem(uhren[1].hSMenu, IDM_TOP, uhren[1].top?MF_CHECKED:MF_UNCHECKED);
                    SetWindowPos(uhren[1].hWnd, uhren[1].top?HWND_TOPMOST:HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                    return TRUE;

                case IDM_TOPZ:
                    uhren[2].top = !uhren[2].top;
                    CheckMenuItem(hPopupMenu, IDM_TOPZ, uhren[2].top?MF_CHECKED:MF_UNCHECKED);
                    CheckMenuItem(uhren[2].hSMenu, IDM_TOP, uhren[2].top?MF_CHECKED:MF_UNCHECKED);
                    SetWindowPos(uhren[2].hWnd, uhren[2].top?HWND_TOPMOST:HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                    return TRUE;

                case IDM_NOSOUND:
                    sound_off = !sound_off;
                    CheckMenuItem(uhren[0].hSMenu, IDM_NOSOUND, sound_off?MF_CHECKED:MF_UNCHECKED);
                    CheckMenuItem(uhren[1].hSMenu, IDM_NOSOUND, sound_off?MF_CHECKED:MF_UNCHECKED);
                    CheckMenuItem(uhren[2].hSMenu, IDM_NOSOUND, sound_off?MF_CHECKED:MF_UNCHECKED);
                    CheckMenuItem(hPopupMenu, IDM_NOSOUND, sound_off?MF_CHECKED:MF_UNCHECKED);
                    DialogBox(NULL, MAKEINTRESOURCE(DLG_STATUS), hwndDlg, (DLGPROC)DlgProcStatus);
                    return TRUE;

                case IDM_NEXT:
                    SetNextEvent();
                    AktToolTip();
                    SaveRect();
                    DialogBox(NULL, MAKEINTRESOURCE(DLG_STATUS), hwndDlg, (DLGPROC)DlgProcStatus);
                    return TRUE;

            }
            break;

        case WM_SYSCOMMAND:
            switch (wParam)
            {
                case SC_RESTORE:
                    ShowWindow(hwndDlg, SW_RESTORE);
                    break;

                case IDM_RESTZEIT:
                // hSysMenu = GetSystemMenu(hwndDlg, FALSE);
                    show_rest = !show_rest;
                    if (show_rest)
                    {
                        CheckMenuItem(uhren[selUhr].hSMenu, IDM_RESTZEIT, MF_CHECKED);
                    }
                    else
                    {
                        CheckMenuItem(uhren[selUhr].hSMenu, IDM_RESTZEIT, MF_UNCHECKED);
                    }
                    return TRUE;

                case IDM_EXIT:
                    SendMessage(hwndDlg, WM_CLOSE, 0, 0);
                    return TRUE;

                case IDM_EDIT:
                    DialogBox(ghInstance, MAKEINTRESOURCE(DLG_EDIT), hwndDlg, (DLGPROC)DlgProcEdit);
                    AktToolTip();
                    SaveRect();
                    return TRUE;

                case IDM_LIST:
                    DialogBox(ghInstance, MAKEINTRESOURCE(DLG_EVENTLIST), hwndDlg, (DLGPROC)DlgProcList);
                    AktToolTip();
                    SaveRect();
                    return TRUE;

                case IDM_STATUS:
                    DialogBox(ghInstance, MAKEINTRESOURCE(DLG_STATUS), hwndDlg, (DLGPROC)DlgProcStatus);
                    return TRUE;

                case IDM_INFO:
                    DialogBox(ghInstance, MAKEINTRESOURCE(DLG_INFO), hwndDlg, (DLGPROC)DlgProcInfo);
                    return TRUE;

                case IDM_SORT:
                    SortList();
                    SaveRect();
                    return TRUE;

                case IDM_HIDE:
                    uhren[selUhr].hide = !uhren[selUhr].hide;
                    CheckMenuItem(hPopupMenu, IDM_HIDEX + selUhr, uhren[selUhr].hide?MF_CHECKED:MF_UNCHECKED);
                    ShowWindow(uhren[selUhr].hWnd, !uhren[selUhr].hide);
                    return TRUE;

                case IDM_TOP:
                    uhren[selUhr].top = !uhren[selUhr].top;
                    CheckMenuItem(uhren[selUhr].hSMenu, IDM_TOP, uhren[selUhr].top?MF_CHECKED:MF_UNCHECKED);
                    CheckMenuItem(hPopupMenu, IDM_TOPX + selUhr, uhren[selUhr].top?MF_CHECKED:MF_UNCHECKED);
                    SetWindowPos(hwndDlg, uhren[selUhr].top?HWND_TOPMOST:HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                    return TRUE;

                case IDM_NOSOUND:
                    sound_off = !sound_off;
                    CheckMenuItem(uhren[0].hSMenu, IDM_NOSOUND, sound_off?MF_CHECKED:MF_UNCHECKED);
                    CheckMenuItem(uhren[1].hSMenu, IDM_NOSOUND, sound_off?MF_CHECKED:MF_UNCHECKED);
                    CheckMenuItem(uhren[2].hSMenu, IDM_NOSOUND, sound_off?MF_CHECKED:MF_UNCHECKED);
                    CheckMenuItem(hPopupMenu, IDM_NOSOUND, sound_off?MF_CHECKED:MF_UNCHECKED);
                    DialogBox(NULL, MAKEINTRESOURCE(DLG_STATUS), hwndDlg, (DLGPROC)DlgProcStatus);
                    return TRUE;

                case IDM_NEXT:
                    SetNextEvent();
                    AktToolTip();
                    SaveRect();
                    DialogBox(ghInstance, MAKEINTRESOURCE(DLG_STATUS), hwndDlg, (DLGPROC)DlgProcStatus);
                    return TRUE;
            }
            break;
#if 0
        case WM_MOUSEMOVE:
            return TRUE;

        case WM_MOUSEHOVER:
            return TRUE;

        case WM_MOUSELEAVE:
            return TRUE;
#endif
        case WM_TIMER:
            // Analoguhr
            if (TIMER_UHRA == wParam)
            {
               static int xx = 0;
                if (uhren[2].hide == 0)
                {
                    static HICON hBTempIcon = NULL;
                    hBTempIcon = CreateBigTimeIcon(hwndDlg);
                    if (NULL != hBTempIcon)
                    {
                        if (NULL != hBIcon)
                        {
                            DestroyIcon(hBIcon);
                        }
                        hBIcon = hBTempIcon;
                        //SendDlgItemMessage(uhren[2].hWnd, IDR_ICO_MAIN, STM_SETICON, (WPARAM)hBTempIcon, (LPARAM)0);
                        SendDlgItemMessage(uhren[2].hWnd, IDI_BCLOCK, STM_SETICON, (WPARAM)hBIcon, (LPARAM)0);
                        //SetClassLong(uhren[2].hWnd, GCL_HICON, (LONG)hBTempIcon);
                    }
                }
                if(xx<3)
                {
                    //TODO
                    Refresh(hwndDlg);
                    xx++;
                }
                return TRUE;
            }
            AktOutput(hwndDlg);
            // Tray-Tip aktualisieren
            GetLocalTime(&Jetzt);
            sprintf(nid.szTip, "%2s: %3d.%02d.%04d\nJetzt: %3d:%02d:%02d\nRest: %3d:%02d:%02d\nEnde: %3d:%02d:%02d",
                    wota[Jetzt.wDayOfWeek], Jetzt.wDay, Jetzt.wMonth, Jetzt.wYear /*%100*/ ,
                    Jetzt.wHour, Jetzt.wMinute, Jetzt.wSecond,
                    RZ.wHour, RZ.wMinute, RZ.wSecond,
                    EZ.wHour, EZ.wMinute, EZ.wSecond);
            nid.hIcon = hIcon;

            // Icons setzen

            static HICON hTempIcon;
            hTempIcon = CreateTimeIcon(hwndDlg);
            if (NULL != hTempIcon)
            {
                if (NULL != hIcon)
                {
                    DestroyIcon(hIcon);
                }
                hIcon = hTempIcon;
                nid.hIcon = hIcon;

                SendDlgItemMessage(uhren[0].hWnd, IDR_ICO_MAIN, STM_SETICON, (WPARAM)hIcon, (LPARAM)0);
                SendDlgItemMessage(uhren[0].hWnd, IDI_ACLOCK, STM_SETICON, (WPARAM)hIcon, (LPARAM)0);
                //SetClassLong(uhren[0].hWnd, GCL_HICON, (size_t)hIcon);
                SendDlgItemMessage(uhren[1].hWnd, IDR_ICO_MAIN, STM_SETICON, (WPARAM)hIcon, (LPARAM)0);
                //SendDlgItemMessage(uhren[1].hWnd, IDI_ACLOCK, STM_SETICON, (WPARAM)hIcon, (LPARAM)0);
                //SetClassLong(uhren[1].hWnd, GCL_HICON, (size_t)hIcon);
                SendDlgItemMessage(uhren[2].hWnd, IDR_ICO_MAIN, STM_SETICON, (WPARAM)hIcon, (LPARAM)0);
                SendMessage(uhren[0].hWnd,WM_SETICON, ICON_SMALL,(LPARAM)hIcon);
                SendMessage(uhren[0].hWnd,WM_SETICON, ICON_BIG  ,(LPARAM)hIcon);
                SendMessage(uhren[1].hWnd,WM_SETICON, ICON_SMALL,(LPARAM)hIcon);
                SendMessage(uhren[1].hWnd,WM_SETICON, ICON_BIG  ,(LPARAM)hIcon);
                SendMessage(uhren[2].hWnd,WM_SETICON, ICON_SMALL,(LPARAM)hIcon);
                SendMessage(uhren[2].hWnd,WM_SETICON, ICON_BIG  ,(LPARAM)hIcon);
            }

            // Tray aktuallisieren
            Shell_NotifyIcon(NIM_MODIFY, &nid);

            if (!done)
            {
                if ((uhren[0].hWnd != 0) &&
                    (uhren[1].hWnd != 0) &&
                    (uhren[2].hWnd != 0))
                {
                    RECT hr;
                    for (i = 0;i < 3; i++)
                    {
                        GetWindowRect(uhren[i].hWnd, &hr);
                        hr.right -= hr.left;
                        hr.bottom -= hr.top;
                        MoveWindow(uhren[i].hWnd, uhren[i].rWndDlg.left, uhren[i].rWndDlg.top, hr.right, hr.bottom, TRUE);
                        char hStr[200];
                        sprintf(hStr,"index:%2d pos x/y:%2ld,%2ld\n",i,uhren[i].rWndDlg.left,uhren[i].rWndDlg.top);
                        OutputDebugString(hStr);
                    }
                }
                done = !done;
            }
            return TRUE;

        case WM_CTLCOLORSTATIC:
            SetColors((HWND)lParam, (HDC) wParam);
            SendMessage(hwndDlg, WM_CTLCOLORDLG, wParam, lParam);
            return (size_t)GetSysColorBrush(COLOR_3DFACE);
            break;

        case WM_CTLCOLORDLG:
            return SetDlgMsgResult((HWND)lParam, uMsg, SetBkfColor(gForegroundColor, gBackgroundColor, (HDC) wParam));
            break;

        case WM_LBUTTONDBLCLK:
            DialogBox(ghInstance, MAKEINTRESOURCE(DLG_EDIT), hwndDlg, (DLGPROC)DlgProcEdit);
            AktToolTip();
            SaveRect();
            break;

#if 0
        case WM_RBUTTONUP:
            //SendMessage(hwndDlg, WM_SYSCOMMAND, IDM_MINI , 0);
            for (i = 0; i < 3; i++)
            {
                if (hwndDlg == uhren[i].hWnd)
                {
                    uhren[i].hide = !uhren[i].hide;
                    CheckMenuItem(hPopupMenu, IDM_HIDEX + i, uhren[i].hide?MF_CHECKED:MF_UNCHECKED);
                    ShowWindow(uhren[i].hWnd, !uhren[i].hide);
                }
            }
            return TRUE;
            break;
#endif

        case WM_MOVE:
        case WM_WINDOWPOSCHANGED:
            for(int i=0; i<3 ;i++)
            {
                if (uhren[i].hide == 0)
                {
                    if (done)
                    {
                        GetWindowRect(uhren[i].hWnd, &uhren[i].rWndDlg);
                    }
                }
            }
            SaveRect();
            return TRUE;
            break;

        case WM_CLOSE:
            KillTimer(hwndDlg, TIMER_UHR);
            KillTimer(hwndDlg, TIMER_UHRA);
            SaveRect();
            nid.cbSize = sizeof(NOTIFYICONDATA);
            nid.hWnd = hwndDlg;
            nid.uID = IDR_ICO_TRAY3;
            nid.uFlags = NIF_ICON + NIF_MESSAGE + NIF_TIP;
            Shell_NotifyIcon(NIM_DELETE, &nid);
            uhren[selUhr].hWnd = NULL;
            EndDialog(hwndDlg, 0);
            exit(0);
            return TRUE;
    }

    return FALSE;
}

static LRESULT CALLBACK DlgProcEdit(HWND hwndEDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    char hStr[100];
    int items;
    int h,m,s;

    switch (uMsg)
    {
        case WM_INITDIALOG:
            sprintf(hStr, "%02d:%02d:%02d", EZ.wHour, EZ.wMinute, EZ.wSecond);
            SetDlgItemText(hwndEDlg, IDD_EDIT_ZEIT, hStr);
            SetDlgItemText(hwndEDlg, IDD_EDIT_WOTA, wochentag);
            SetDlgItemText(hwndEDlg, IDD_EDIT_GRUND, alarmgrund);
            return TRUE;

        case WM_COMMAND:
            switch (GET_WM_COMMAND_ID(wParam, lParam))
            {
                case IDOK:
                    GetDlgItemText(hwndEDlg, IDD_EDIT_ZEIT, hStr, 99);
                    items = sscanf(hStr, "%u:%u:%u", &h, &m, &s);
                    // eine Einfache Syntaxprüfung der Eingabe  ** aN 09.08.2023
                    switch(items)
                    {
                        case 3:
                            EZ.wHour   = h % 24;
                            EZ.wMinute = m % 60;
                            EZ.wSecond = s % 60;
                            erreicht = 0;
                            break;
                        case 2:
                            EZ.wHour   = h % 24;
                            EZ.wMinute = m % 60;
                            EZ.wSecond = 0;
                            erreicht = 0;
                            break;
                        case 1:
                            GetLocalTime(&EZ);
                            EZ.wSecond = 0;
                            AddTime(h);
                            erreicht = 0;
                            break;
                        default:
                            break;
                    }

                    GetDlgItemText(hwndEDlg, IDD_EDIT_GRUND, alarmgrund, 100);
                    dotrim(alarmgrund);
                    GetDlgItemText(hwndEDlg, IDD_EDIT_WOTA, wochentag, 3);
                    AdjustWT(wochentag);
                    SaveRect();

                    EndDialog(hwndEDlg, TRUE);
                    return TRUE;

                case IDCANCEL:
                    EndDialog(hwndEDlg, FALSE);
                    return TRUE;
            }
            break;

        case WM_CLOSE:
            EndDialog(hwndEDlg, 0);
            return TRUE;

    }

    return FALSE;
}

static LRESULT CALLBACK DlgProcAlarm(HWND hwndADlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    char hStr[120];

    switch (uMsg)
    {
        case WM_INITDIALOG:
            AlarmDlg = 1;
            erreicht = 1;
            sprintf(hStr, "%02d:%02d:%02d   %s", EZ.wHour, EZ.wMinute, EZ.wSecond, alarmgrund);
            SetDlgItemText(hwndADlg, IDD_ALARM_TEXT, hStr);
            PlayResource(MAKEINTRESOURCE(IDR_SND_FANFARE));
            return TRUE;

        case WM_COMMAND:
            switch (GET_WM_COMMAND_ID(wParam, lParam))
            {
                case IDD_5MIN:
                    AddTime(5);
                    break;

                case IDD_15MIN:
                    AddTime(15);
                    break;

                case IDD_30MIN:
                    AddTime(30);
                    break;

                case IDD_60MIN:
                    AddTime(60);
                    break;

                case IDD_EDIT:
                    EndDialog(hwndADlg, 0);
                    DialogBox(ghInstance, MAKEINTRESOURCE(DLG_EDIT), hwndADlg, (DLGPROC)DlgProcEdit);
                    AktToolTip();
                    SaveRect();
                    break;

                case IDD_WEITER:
                    SetNextEvent();
                    AktToolTip();
                    SaveRect();
                    break;

                case IDD_STOPP:
                    break;

            }
            AlarmDlg = 0;
            EndDialog(hwndADlg, 0);
            DialogBox(ghInstance, MAKEINTRESOURCE(DLG_STATUS), hwndADlg, (DLGPROC)DlgProcStatus);
            return TRUE;

        case WM_RBUTTONDBLCLK:
        case WM_RBUTTONUP:
            DialogBox(ghInstance, MAKEINTRESOURCE(DLG_EDIT), hwndADlg, (DLGPROC)DlgProcEdit);
            AktToolTip();
            SaveRect();
            AlarmDlg = 0;
            EndDialog(hwndADlg, 0);
            return TRUE;

        case WM_LBUTTONDBLCLK:
        case WM_LBUTTONUP:
        case WM_CLOSE:
            AlarmDlg = 0;
            SetNextEvent();
            AktToolTip();
            SaveRect();
            EndDialog(hwndADlg, 0);
            return TRUE;
    }

    return FALSE;
}

static LRESULT CALLBACK DlgProcList(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
            SetList(hwndDlg);
            return TRUE;

        case WM_COMMAND:
            switch (GET_WM_COMMAND_ID(wParam, lParam))
            {
                case IDOK:
                    GetList(hwndDlg);
                    // und speichern
                    SaveRect();
                    EndDialog(hwndDlg, TRUE);
                    return TRUE;

                case IDD_IN_LISTE:
                    GetList(hwndDlg);
                    AktEvent2Liste();
                    SetList(hwndDlg);
                    SaveRect();
                    return TRUE;

                case IDD_SORT_LISTE:
                    GetList(hwndDlg);
                    SortList();
                    SetList(hwndDlg);
                    SaveRect();
                    return TRUE;

                case IDD_NEXT_LISTE:
                    // Liste lesen
                    GetList(hwndDlg);
                    SetNextEvent();
                    SetList(hwndDlg);
                    SaveRect();
                    return TRUE;

                case IDCANCEL:
                    EndDialog(hwndDlg, FALSE);
                    return TRUE;
            }
            break;

        case WM_CLOSE:
            EndDialog(hwndDlg, TRUE);
            return TRUE;

    }

    return FALSE;
}

static LRESULT CALLBACK DlgProcInfo(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    char outstr[300];

    switch (uMsg)
    {
        case WM_INITDIALOG:
            GetMyVersion(outstr);
            SetDlgItemText(hwndDlg, IDD_TEXT_INFO, outstr);
            return TRUE;

        case WM_COMMAND:
        case WM_CLOSE:
        case WM_LBUTTONUP:
        case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDBLCLK:
            EndDialog(hwndDlg, 0);
            return TRUE;
    }

    return FALSE;
}

static LRESULT CALLBACK DlgProcStatus(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    char outstr[300];

    switch (uMsg)
    {
        case WM_INITDIALOG:
            SetTimer(hwndDlg, TIMER_STATUS, 5000, NULL);
            sprintf(outstr, "Zeit : %2d:%02d:%02d\r\nAlarm: %s\r\nTon  : %s",
                    EZ.wHour,EZ.wMinute,EZ.wSecond,
                    alarmgrund,
                    (sound_off)?"aus":"an");
            SetDlgItemText(hwndDlg, IDD_STATUS, outstr);
            return TRUE;

        case WM_TIMER:
            KillTimer(hwndDlg, TIMER_STATUS);
            EndDialog(hwndDlg, 0);
            return TRUE;

        case WM_CLOSE:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
            EndDialog(hwndDlg, 0);
            return TRUE;
    }

    return FALSE;
}
