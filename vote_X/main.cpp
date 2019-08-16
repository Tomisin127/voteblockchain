#include <windows.h>
#include <stdlib.h>
#include "all_headers.h"
//#include "include/boost/lexical_cast.hpp"

//using boost::lexical_cast;

//BACKGROUND BITMAP "vote_background.bmp"
#define SUBMIT_BUTTON_CLICKED 9
#define ID_LIST 3
#define FILE_MENU_NEW 0
#define FILE_MENU_EXIT 1

//#define SSTR(x) static_cast<std::ostringstream & >( \
  //      (std::ostringstream() <<std::dec << x ) ).str()

template <typename T>
string number_to_str(T num)
{
    ostringstream ostr_stream;
    ostr_stream << num ;
    return ostr_stream.str();

}

bool is_submitted;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HMENU h_menu;

HWND h_name,h_age,h_out,h_logo,h_imageview;

HWND h_candidate_name, h_submit_button,h_list;

HWND h_surname,h_blocklist,h_vote_count_list;

HWND h_block;

HWND h_blocklist1,h_blocklist2,h_blocklist3,h_blocklist4,h_blocklist5,h_blocklist6,h_blocklist7;

HBITMAP h_logo_image;

VoteBlockChain data;


VoterData info;
//HWND hEdit;

//HBITMAP hLogoImage, hGenerateImage;

//void add_menu(HWND);

void control_node(HWND);

void menu(HWND);

void load_images();

void table_of_result(HWND);

int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE h_previnstance,  LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = {0};

    //wc.hbrBackground = CreatePatternBrush( LoadBitmapW(GetModuleHandle(0), MAKEINTRESOURCE(BACKGROUND)) );
    wc.hbrBackground = GetSysColorBrush(COLOR_3DLIGHT);
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = h_instance;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;


    //MessageBox(NULL,"HELLO WORLD", "MY FIRST GUI", MB_OK);

    if (!RegisterClassW(&wc))
        return -1;


    CreateWindowW(L"myWindowClass", L"Vote X", WS_OVERLAPPEDWINDOW |WS_MAXIMIZE| WS_VISIBLE, 100,100,640,640,
                  NULL,NULL,NULL,NULL);

    MSG msg = {0};

    //cout << "THIS PROGRAM IS A BLOCKCHAIN THAT RECORDS VOTING INFORMATION IN A PUBLIC LEDGER\n" <<endl;
	//cout << "candidate1-> pelumi and candidate2-> john\n\n\n" <<endl;
	//cout << "enter your first name: (enter q to quit) \n" <<endl;
    //the block chain data
	//VoteBlockChain dat;

    while(GetMessage(&msg,NULL,NULL,NULL))
    {

        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (is_submitted==true)

        {


                char *name = new char[100];
                char *surname = new char[100];
                char *age = new char[100];
                char *candidate_name = new char[100];

                GetWindowText(h_name,name,strlen(name)+10);
                GetWindowText(h_surname,surname,strlen(surname)+10);
                GetWindowText(h_age,age,strlen(age)+10);
                GetWindowText(h_candidate_name,candidate_name,strlen(candidate_name)+10);


                string fn(name,strlen(name));
                string ln(surname,strlen(surname));
                string cn(candidate_name,strlen(candidate_name));



                time_t data_time;

                info.firstname = fn;

                info.lastname = ln;
                //info.age = age;`
                info.candidate = cn;
                info.timestamp = data_time;

                data.addBlock(info);
                data.candidate_vote_count(info);
               // cout <<"name : "<<info.firstname <<endl;
                //cout << "candidate: " << info.candidate <<endl;
                data.print_chain();

                is_submitted=false;

                delete []candidate_name;
                delete []age;
                delete []surname;
                delete []name;




        }

                //is_submitted = false;


/*
		//time of vote

		time_t datatime;

		//each voter block info
		VoterData info;

		cin>>info.firstname;



		cout << "enter your last name: " <<endl;
		cin>>info.lastname;

		cout << "enter your age: " <<endl;
		cin>>info.age;

		cout << "enter the candidate you vote for " <<endl;
		cin>>info.candidate;

		//add the voter info and choice of candidate in vote blockchain
		dat.addBlock(info);

		dat.candidate_vote_count(info);

		cout << endl;

		//data.print_vote_count();
		dat.print_chain();

		dat.print_vote_count();

		dat.read_bio_information();

		cout << endl;

		if (cin.get()=='q')
			break;


		cout << "enter your first name: (enter q to quit) " <<endl;
		cout << "candidate1-> pelumi and candidate2-> john" <<endl;

		*/

	}


    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{

    switch(msg)
    {

    /*case FILE_MENU_NEW:
        MessageBeep(MB_OK);

    case FILE_MENU_EXIT:
        MessageBeep(MB_COMPOSITE);
    */

  /*  case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc;
            BITMAP bitmap;
            HDC hdc_mem;
            HGDIOBJ old_bitmap;
            h_bitmap01 = (HBITMAP)LoadImageW(NULL,L"c:\\vote_background.bmp", IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

            hdc = BeginPaint(hwnd, &ps);

            hdc_mem = CreateCompatibleDC(hdc);
            old_bitmap = SelectObject(hdc_mem,h_bitmap01);

            GetObjectW(h_bitmap01,sizeof(bitmap),&bitmap);
            BitBlt(hdc,0,0,bitmap.bmWidth,bitmap.bmHeight,hdc_mem,0,0,SRCCOPY);

            SelectObject(hdc_mem, old_bitmap);
            DeleteDC(hdc_mem);
            EndPaint(hwnd, &ps);
        }
            */
    case WM_CREATE:

        menu(hwnd);
        load_images();
        control_node(hwnd);
        table_of_result(hwnd);
        break;

    case WM_COMMAND:
        switch(wp)
            {
            case SUBMIT_BUTTON_CLICKED:

                is_submitted = true;

                //MessageBoxW(hwnd,L"submitted",L"OK",MB_OK);
               // MessageBeep(MB_OK);





                vector<VoteBlock>::iterator it;

                for(it =data.getchain().begin(); it !=data.getchain().end() ; ++it)
                {
                    cout << endl;
                    VoteBlock current= *it;
                    cout << " BLOCK=======================" <<endl;
                    SetWindowText(h_blocklist, number_to_str(current.getIndex()).c_str());
                    SetWindowText(h_blocklist1, (current.data.firstname).c_str());
                    SetWindowText(h_blocklist2, (current.data.lastname).c_str());
                    SetWindowText(h_blocklist3, (current.data.candidate).c_str());
                    SetWindowText(h_blocklist4, number_to_str(current.data.timestamp).c_str());
                    SetWindowText(h_blocklist5, number_to_str(current.getHash()).c_str());
                    SetWindowText(h_blocklist6, number_to_str(current.getpreviousHash()).c_str());
                    SetWindowText(h_blocklist7, number_to_str(current.isHashValid()).c_str());

                }




               break;

                }

        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;




    default:
        return DefWindowProcW(hwnd, msg,wp,lp);
    }

}

void menu(HWND hwnd)
{
    h_menu = CreateMenu();

    //sub menu
    HMENU h_filemenu = CreateMenu();
    HMENU h_submenu = CreateMenu();
    HMENU h_settings = CreateMenu();

    AppendMenuW(h_submenu, MF_STRING,NULL, L"Sub menu");
    //AppendMenuW(hSubMenu, MF_STRING,CHANGE_TITLE, L"CHANGE TITLE");

    AppendMenuW(h_filemenu, MF_STRING,FILE_MENU_NEW, L"New");
    AppendMenuW(h_filemenu, MF_POPUP,(UINT_PTR)h_submenu, L"Open SubMenu");
    AppendMenuW(h_filemenu,MF_SEPARATOR,NULL,NULL);
    AppendMenuW(h_filemenu, MF_STRING,FILE_MENU_EXIT, L"Exit");

    AppendMenuW(h_menu,MF_POPUP, (UINT_PTR)h_filemenu ,L"File");

    AppendMenuW(h_menu,MF_STRING,NULL,L"Help");

    AppendMenuW(h_menu,MF_STRING, NULL, L"Settings");

    SetMenu(hwnd,h_menu );
}


void control_node(HWND hwnd)
{
//STATIC CONTROL
 //   CreateWindowW(L"Static", L"Enter Text Here : ", WS_VISIBLE | WS_CHILD|WS_BORDER|SS_CENTER, 200,100,100,50,hWnd,NULL,NULL,NULL);

    //EDIT CONTROL
    //hEdit = CreateWindowW(L"Edit", L"...",WS_VISIBLE| WS_CHILD|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL, 200,152,100,50,hWnd, NULL,NULL,NULL);

    //CreateWindowW(L"Button", L"Change Title", WS_VISIBLE| WS_CHILD,200,204,100,50,hWnd, (HMENU)CHANGE_TITLE,NULL,NULL);

    CreateWindowW(L"Static", L"Your Name : " , WS_VISIBLE| WS_CHILD|WS_BORDER,100,50,98,38,hwnd, NULL,NULL,NULL);
    h_name = CreateWindowW(L"Edit", L"", WS_VISIBLE |WS_CHILD|WS_BORDER|ES_MULTILINE |ES_AUTOVSCROLL,200,50,98,38,hwnd,NULL,NULL,NULL);

    CreateWindowW(L"Static", L"Your Surname : " , WS_VISIBLE| WS_CHILD |WS_BORDER,100,100,120,38,hwnd, NULL,NULL,NULL);
    h_surname = CreateWindowW(L"Edit", L"", WS_VISIBLE |WS_CHILD|WS_BORDER|ES_MULTILINE |ES_AUTOVSCROLL,200,100,98,38,hwnd,NULL,NULL,NULL);


    CreateWindowW(L"Static", L" Your Age " , WS_VISIBLE| WS_CHILD| WS_BORDER,100,150,98,38,hwnd, NULL,NULL,NULL);
    h_age = CreateWindowW(L"Edit", L"", WS_VISIBLE |WS_CHILD|WS_BORDER|ES_MULTILINE |ES_AUTOVSCROLL,200,150,98,38,hwnd,NULL,NULL,NULL);

    CreateWindowW(L"Static", L"NAME OF CANDIDATE YOU WANT TO VOTE" , WS_VISIBLE| WS_CHILD| WS_BORDER,100,200,290,38,hwnd, NULL,NULL,NULL);

    CreateWindowW(L"Static", L"Candidate Name : " , WS_VISIBLE| WS_CHILD|WS_BORDER,100,250,98,38,hwnd, NULL,NULL,NULL);
    h_candidate_name = CreateWindowW(L"Edit", L"", WS_VISIBLE |WS_CHILD|WS_BORDER|ES_MULTILINE |ES_AUTOVSCROLL,200,250,98,38,hwnd,NULL,NULL,NULL);

    //CreateWindowW(L"Static",L"Age : " , WS_VISIBLE| WS_CHILD,100,50,98,38,hWnd, NULL,NULL,NULL);
    //hAge = CreateWindowW(L"Edit", L"", WS_VISIBLE |WS_CHILD|WS_BORDER,200,90,98,38,hWnd,NULL,NULL,NULL);

    h_submit_button = CreateWindowW(L"Button", L"SUBMIT", WS_VISIBLE |WS_CHILD|BS_BITMAP,150,300,98,38,hwnd,(HMENU)SUBMIT_BUTTON_CLICKED,NULL,NULL);
    //SendMessageW(h_submit_button,BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hGenerateImage);

   // hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE |WS_CHILD|WS_BORDER,100,200,300,200,hWnd,NULL,NULL,NULL);

    //TO LOAD AN IMAGE ON THE SCREEN
    h_logo = CreateWindowW(L"Static",NULL , WS_VISIBLE| WS_CHILD|SS_BITMAP,350,60,100,100,hwnd, NULL,NULL,NULL);
    // SEND A MESSAGE TO THE WINDOW PROCEEDURE OF THIS CONTROL TO KNOW ABOUT THE IMAGE
    SendMessageW(h_logo,STM_SETIMAGE, IMAGE_BITMAP,(LPARAM)h_logo_image);
}

void load_images()
{
    h_logo_image = (HBITMAP)LoadImageW(NULL,L"vote_background.bmp", IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

}

void table_of_result(HWND hwnd)
{
   // InitCommonControls();
    h_block = CreateWindowW(L"Static", L"-------BLOCK LIST---------" , WS_VISIBLE| WS_CHILD|ES_CENTER,500,100,150,64,hwnd, NULL,NULL,NULL);
    h_blocklist = CreateWindowW(L"Static", NULL , WS_VISIBLE| WS_CHILD|WS_BORDER|ES_CENTER ,500,150,150,64,hwnd, NULL,NULL,NULL);
    h_blocklist1 = CreateWindowW(L"Static", NULL , WS_VISIBLE| WS_CHILD |WS_BORDER|ES_CENTER ,500,200,150,64,hwnd, NULL,NULL,NULL);
    h_blocklist2 = CreateWindowW(L"Static", NULL , WS_VISIBLE| WS_CHILD|WS_BORDER |ES_CENTER,500,250,150,64,hwnd, NULL,NULL,NULL);
    h_blocklist3 = CreateWindowW(L"Static", NULL , WS_VISIBLE| WS_CHILD |WS_BORDER|ES_CENTER,500,300,150,64,hwnd, NULL,NULL,NULL);
    h_blocklist4 = CreateWindowW(L"Static", NULL , WS_VISIBLE| WS_CHILD|WS_BORDER |ES_CENTER,500,350,150,64,hwnd, NULL,NULL,NULL);
    h_blocklist5 = CreateWindowW(L"Static", NULL , WS_VISIBLE| WS_CHILD |WS_BORDER|ES_CENTER,500,400,150,64,hwnd, NULL,NULL,NULL);
    h_blocklist6 = CreateWindowW(L"Static", NULL , WS_VISIBLE| WS_CHILD|WS_BORDER|ES_CENTER|WS_HSCROLL,500,450,150,64,hwnd, NULL,NULL,NULL);
    h_blocklist7 = CreateWindowW(L"Static", NULL , WS_VISIBLE| WS_CHILD|WS_BORDER|ES_CENTER,500,550,150,64,hwnd, NULL,NULL,NULL);




   /* h_vote_count_list = CreateWindow(WC_LISTVIEW, "",
         WS_VISIBLE|WS_BORDER|WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
         500, 500, 640, 300,
         hwnd, (HMENU)ID_LIST, GetModuleHandleW(0), 0); */
}
