// PIA_Equipo_5.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "PIA_Equipo_5.h"
#include <string>
#include <Commdlg.h>
#include <fstream>
#define MAX_LOADSTRING 100
using namespace std;

struct EMPLEADO {
    char nombre[255];
    char rfc[15];
    char usuario[100] = { 0 };
    char password[100] = { 0 };
    char imagen[255];
};

struct NODOEMPLEADO {
    NODOEMPLEADO* anterior;
    EMPLEADO empleado;
    NODOEMPLEADO* siguiente;
};

NODOEMPLEADO* origenEmpleado = NULL,
* finalEmpleado = NULL;

struct SALAS {
    int númeroDeSala;
    int númeroDeAsientos;
};

struct NODOSALAS {
    NODOSALAS* anterior;
    SALAS salas;
    NODOSALAS* siguiente;
};

NODOSALAS* primeraSala = NULL,
* últimaSala = NULL;

struct FUNCIONES {
    char nombreDePelícula[255];
    int duración;
    char clasificación[1];
    char idioma[255];
    int númeroDeSala;
    int númeroDeAsientos;
    char fechaDeInicio[100];
    char fechaDeFin[100];
    int hora;
    int precio;
    char imagen[255];
};

struct NODOFUNCIONES {
    NODOFUNCIONES* anterior;
    FUNCIONES funciones;
    NODOFUNCIONES* siguiente;
};

NODOFUNCIONES* primeraFunción = NULL,
* últimaFunción = NULL;

struct VENTAS {
    char formaDePago[100];
    char fecha;
    int  boletos;
    int  precio;
};

struct NODOVENTAS {
    NODOVENTAS* anterior;
    VENTAS ventas;
    NODOVENTAS* siguiente;
};

NODOVENTAS* primeraVenta = NULL,
* últimaVenta = NULL;

// Variables globales:
HINSTANCE hInst;                                // instancia actual
HWND ventanaPrincipal;
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal
char nombre[255] = { 0 };
char rfc[15] = { 0 };
char usuario[100] = { 0 };
char password[100] = { 0 };
char imagen[255] = { 0 };

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CallbackVentanaPrincipal(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CallbackRegistrarEmpleado(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CallbackPerfildeEmpleado(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);                                                               
LRESULT CALLBACK CallbackRegistrodeEmpleados(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CallbackRegistrodeSalas(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CallbackRegistrodeFunciones(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CallbackFuncionesRegistradas(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CallbackReportedeVentas(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool menuOpciones(HWND ventana, int opciones);
NODOEMPLEADO* crearNodoEmpleado(string nombre, string rfc, string usuario, string password, string imagen);
bool agregarEmpleadoAlFinal(NODOEMPLEADO* empleado);
NODOEMPLEADO* buscarEmpleadoPorNombre(string nombre);
NODOEMPLEADO* buscarEmpleadoPorUsuario(string usuario);
bool eliminarEmpleadoAlInicio();
bool eliminarEmpleadoAlFinal();
bool eliminarEmpleadoAlMedio(string nombre);
void imprimirLista();
void guardarArchivoEmpleados();
void leerArchivoEmpleados();
wstring s2ws(const std::string& s, bool isUtf8 = true);
NODOSALAS* crearNodoSala(int númeroDeSala, int númeroDeAsientos);
bool agregarSalaAlFinal(NODOSALAS* salas);
//NODOSALAS* buscarSalaPorNúmeroDeSala(int númeroDeSala);
void imprimirListaSalas();
void guardarArchivoSalas();
void leerArchivoSalas();
NODOFUNCIONES* crearNodoFunciones(string nombreDePelícula, int duración, string clasificación, string idioma, int númeroDeSala, int númeroDeAsientos,
    string fechaDeInicio, string fechaDeFin, int hora, int precio, string imagen);
bool agregarFuncionAlFinal(NODOFUNCIONES* funciones);
NODOFUNCIONES* buscarFunciónPorNombreDePelícula(string nombreDePelícula);
bool eliminarFunciónAlInicio();
bool eliminarFunciónAlFinal();
bool eliminarFunciónAlMedio(string nombreDePelícula);
void imprimirListaFunciones();
void guardarArchivoFunciones();
void leerArchivoFunciones();
NODOVENTAS* crearNodoVentas(string formaDePago, string fecha, int boletos, int precio);
bool agregarVentaAlFinal(NODOVENTAS* ventas);
NODOVENTAS* buscarFuncionPorPagoYFecha(string formaDePago, string fecha);
void imprimirListaVentas();
void guardarArchivoVentas();
void leerArchivoVentas();
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Colocar código aquí.
    leerArchivoEmpleados();
    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PIAEQUIPO5, szWindowClass, MAX_LOADSTRING);
    hInst = hInstance;
    ventanaPrincipal = CreateDialog(hInst,
        MAKEINTRESOURCE(IDD_INICIO_DE_SESION),NULL, WndProc);
    ShowWindow(ventanaPrincipal, SW_SHOW);
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PIAEQUIPO5));

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG)); 

    // Bucle principal de mensajes:
    while (ventanaPrincipal != NULL &&
        GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(ventanaPrincipal,
            hAccelTable, &msg) &&
            !IsDialogMessage(ventanaPrincipal, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    guardarArchivoEmpleados();
    return (int) msg.wParam;
}
/*ANGEL*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizar las selecciones de menú:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDC_INICIAR_SESION: {
                char usuario[100] = { 0 };
                char password[100] = { 0 };
                // Obtener el texto ingresado por el usuario en los controles de edición
                GetDlgItemTextA(hWnd, IDC_USUARIO, usuario, 100);
                GetDlgItemTextA(hWnd, IDC_CONTRASENA, password, 100);

                // Verificar si el usuario ha ingresado tanto el usuario como la contraseña
                if (strlen(usuario) == 0) {
                    MessageBox(hWnd, "Ingresa usuario", "Error", MB_OK);
                    break;
                }
                if (strlen(password) == 0) {
                    MessageBox(hWnd, "Ingresa password", "Error", MB_OK);
                    break;
                }
                if (origenEmpleado == NULL) {
                    // Crear un nuevo nodo para el usuario administrador
                    NODOEMPLEADO* admin = crearNodoEmpleado("Admin", "admin123", "admin", "admin12345", "");

                    // Agregar el nodo del administrador a la lista de empleados
                    agregarEmpleadoAlFinal(admin);
                }
                NODOEMPLEADO* busqueda_user = buscarEmpleadoPorUsuario(usuario);
                if (busqueda_user == NULL) {
                    MessageBox(hWnd, "Usuario invalido", "Login", MB_ICONERROR);
                    break;
                }
                if (strcmp(busqueda_user->empleado.password,password) != 0) {
                    MessageBox(hWnd, "Password incorrecto", "Login", MB_ICONERROR);
                    break;
                }
                NODOEMPLEADO*  usuarioLoggeado = busqueda_user;
                HWND nuevaVentana =
                    CreateDialog(hInst,
                        MAKEINTRESOURCE(IDD_Venta_de_boletos),
                        NULL, CallbackVentanaPrincipal);
                ShowWindow(nuevaVentana, SW_SHOW);
                EndDialog(hWnd, 0);
                ventanaPrincipal = nuevaVentana;
            }break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDC_SALIR:
            case WM_CLOSE: 
            case WM_DESTROY: {
                EndDialog(hWnd, 0);
                ventanaPrincipal = NULL;
            }break;
            default:{}
                // return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Agregar cualquier código de dibujo que use hDC aquí...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:{}
        // return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
// Controlador de mensajes del cuadro Acerca de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

LRESULT CALLBACK CallbackRegistrarEmpleado(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
    case WM_CREATE: {
        return TRUE;
    }break;
    case WM_COMMAND: {
        int opcion = LOWORD(wParam);
        if (LOWORD(wParam) == IDC_insertar_imagen && HIWORD(wParam) == BN_CLICKED) {
            OPENFILENAME ofn;
            ZeroMemory(&ofn, sizeof(OPENFILENAME));
            char cDirFile[MAX_PATH] = "";

            ofn.hwndOwner = hWnd;
            ofn.lpstrFile = cDirFile;
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.nMaxFile = MAX_PATH;
            ofn.lpstrDefExt = "txt";
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
            ofn.lpstrFilter = "Archivos de Texto\0*.txt\0Imagenes BMP\0*.bmp\0Todos los Archivos\0*.*\0";
            if (GetOpenFileName(&ofn)) {
                HWND hPControl = GetDlgItem(hWnd, PC_IMAGE);
                HBITMAP hImage = (HBITMAP)LoadImage(NULL, cDirFile, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
                SendMessage(hPControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
            }
            else {
                // El usuario canceló la selección de la imagen
                MessageBox(hWnd, TEXT("No se seleccionó ninguna imagen."), TEXT("Información"), MB_OK);
                break;
            }
        }
        if (menuOpciones(hWnd, opcion))
            return FALSE;
        switch (opcion) {
        // Analizar las selecciones de menú:
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDC_Guardar: {

            GetDlgItemTextA(hWnd, IDC_NOMBRE, nombre, 255);
            GetDlgItemTextA(hWnd, IDC_RFC,rfc, 15);
            GetDlgItemTextA(hWnd, IDC_CLAVE_USUARIO, usuario, 100);
            GetDlgItemTextA(hWnd, IDC_PASSWORD, password, 100);
            GetDlgItemTextA(hWnd, PC_IMAGE, imagen, 255);
            
            if (strlen(nombre) == 0) {
                MessageBox(hWnd, "Ingresa un nombre", "Error", MB_OK);
                break;
            }
            if (strlen(rfc) == 0) {
                MessageBox(hWnd, "Ingresa un RFC", "Error", MB_OK);
                break;
            }
            if (strlen(usuario) == 0) {
                MessageBox(hWnd, "Ingresa usuario", "Error", MB_OK);
                break;
            }
            if (strlen(password) == 0) {
                MessageBox(hWnd, "Ingresa password", "Error", MB_OK);
                break;
            }

            NODOEMPLEADO* busqueda = buscarEmpleadoPorNombre(nombre);
            if (busqueda != NULL) {
                MessageBox(hWnd, "Ya existe nombre", "Error", 0);
                break;
            }
            if (nombre == "Admin") {
                MessageBox(hWnd, "Ya existe nombre", "Error", 0);
                break;
            }
            NODOEMPLEADO* busqueda_usuario = buscarEmpleadoPorUsuario(usuario);
            if (busqueda_usuario != NULL) {
                MessageBox(hWnd, "Ya existe usuario", "Error", 0);
                break;
            }
            if (usuario == "admin") {
                MessageBox(hWnd, "Ya existe usuario", "Error", 0);
                break;
            }
            NODOEMPLEADO* nuevo = crearNodoEmpleado(nombre, rfc, usuario, password, imagen); 
            agregarEmpleadoAlFinal(nuevo);
            MessageBox(hWnd, "Agregado con exito", "Success", 0);

        }break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDC_SALIR:
        case WM_CLOSE:
        case WM_DESTROY: {
            EndDialog(hWnd, 0);
            ventanaPrincipal = NULL;
        }break;
        default: {}
        
        }
    }break;
    }
    return FALSE;
}
LRESULT CALLBACK CallbackPerfildeEmpleado(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG:
    case WM_CREATE: {
        NODOEMPLEADO* busqueda_user = buscarEmpleadoPorUsuario(usuario);
        NODOEMPLEADO* usuarioLoggeado = busqueda_user;
        if (usuarioLoggeado != NULL) {
            SetDlgItemTextA(hWnd, IDC_NOMBRE, usuarioLoggeado->empleado.nombre);
            SetDlgItemTextA(hWnd, IDC_RFC, usuarioLoggeado->empleado.rfc);
            SetDlgItemTextA(hWnd, IDC_USUARIO, usuarioLoggeado->empleado.usuario);
            SetDlgItemTextA(hWnd, IDC_PASSWORD, usuarioLoggeado->empleado.password);
            SetDlgItemTextA(hWnd, IDC_FOTO, usuarioLoggeado->empleado.imagen);
        }
        return TRUE;
    }
    case WM_ACTIVATE: {
        ventanaPrincipal = hWnd;
    }break;
    case WM_COMMAND: {
        int opcion = LOWORD(wParam);

        if (menuOpciones(hWnd, opcion))
            return FALSE;
        switch (opcion) {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDC_MODIFICAR: {
            HWND nuevaVentana =
                CreateDialog(hInst,
                    MAKEINTRESOURCE(IDD_Registro_de_usuario),
                    NULL, CallbackRegistrarEmpleado);
            ShowWindow(nuevaVentana, SW_SHOW);
            EndDialog(hWnd, 0);
            ventanaPrincipal = nuevaVentana; 
        }break;
        case IDC_Eliminar: {

        }break;
        case IDC_AGREGAR: {
            HWND nuevaVentana =
                CreateDialog(hInst,
                    MAKEINTRESOURCE(IDD_Registro_de_usuario),
                    NULL, CallbackRegistrarEmpleado);
            ShowWindow(nuevaVentana, SW_SHOW);
            EndDialog(hWnd, 0);
            ventanaPrincipal = nuevaVentana;
        }break;
        }
    }break;
    }
    return FALSE;
}
LRESULT CALLBACK CallbackRegistrodeEmpleados(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG:
    case WM_CREATE: {
        NODOEMPLEADO* indice = origenEmpleado;
        while (indice != NULL) {
            string nombre(indice->empleado.nombre);
            SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_ADDSTRING,
                0, (LPARAM)nombre.c_str());

            HWND hwndEdit = GetDlgItem(hWnd, IDC_EMPLEADO);

            SetWindowText(hwndEdit, nombre.c_str());
            indice = indice->siguiente;
        }
        return TRUE;
    }break;
    case WM_ACTIVATE: {
        ventanaPrincipal = hWnd;
    }break;
    case WM_COMMAND: {
        int opcion = LOWORD(wParam);
        if (menuOpciones(hWnd, opcion))
            return FALSE;
        switch (opcion) {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDC_MODIFICAR_2: {
            HWND nuevaVentana =
                CreateDialog(hInst,
                    MAKEINTRESOURCE(IDD_Registro_de_usuario),
                    NULL, CallbackRegistrarEmpleado);
            ShowWindow(nuevaVentana, SW_SHOW);
            EndDialog(hWnd, 0);
            ventanaPrincipal = nuevaVentana;
        }break;
        }
    }break;
    }
    return FALSE;
}
LRESULT CALLBACK CallbackRegistrodeSalas(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG:
    case WM_CREATE: {
        return TRUE;
    }break;
    case WM_ACTIVATE: {
        ventanaPrincipal = hWnd;
    }break;
    case WM_COMMAND: {
        int opcion = LOWORD(wParam);
        if (menuOpciones(hWnd, opcion))
            return FALSE;
        switch (opcion) {
        }
    }break;
    }
    return FALSE;
}
/*ANDREA*/
LRESULT CALLBACK CallbackVentanaPrincipal(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case WM_INITDIALOG:
        case WM_CREATE: {
            return TRUE;
        }break;
        case WM_ACTIVATE: {
            ventanaPrincipal = hWnd;
        }break;
        case WM_COMMAND: {
            int opcion = LOWORD(wParam);
            if (menuOpciones(hWnd, opcion))
                return FALSE;
            switch (opcion) {
            }
        }break;
    }
    return FALSE;
}
LRESULT CALLBACK CallbackRegistrodeFunciones(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG:
    case WM_CREATE: {
        return TRUE;
    }break;
    case WM_ACTIVATE: {
        ventanaPrincipal = hWnd;
    }break;
    case WM_COMMAND: {
        int opcion = LOWORD(wParam);
        if (menuOpciones(hWnd, opcion))
            return FALSE;
        switch (opcion) {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDC_VER_REGISTRO: {
            HWND nuevaVentana =
                CreateDialog(hInst,
                    MAKEINTRESOURCE(IDD_FUNCIONES_REGISTRADAS),
                    NULL, CallbackFuncionesRegistradas);
            ShowWindow(nuevaVentana, SW_SHOW);
            EndDialog(hWnd, 0);
            ventanaPrincipal = nuevaVentana;
        }break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDC_SALIR:
        case WM_CLOSE:
        case WM_DESTROY: {
            EndDialog(hWnd, 0);
            ventanaPrincipal = NULL;
        }break;
        default: {}
               // return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    }
    return FALSE;
}
LRESULT CALLBACK CallbackFuncionesRegistradas(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG:
    case WM_CREATE: {
        return TRUE;
    }break;
    case WM_ACTIVATE: {
        ventanaPrincipal = hWnd;
    }break;
    case WM_COMMAND: {
        int opcion = LOWORD(wParam);
        if (menuOpciones(hWnd, opcion))
            return FALSE;
        switch (opcion) {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDC_MODIFICAR_3: {
            HWND nuevaVentana =
                CreateDialog(hInst,
                    MAKEINTRESOURCE(IDD_REGISTRO_DE_FUNCIONES),
                    NULL, CallbackRegistrodeFunciones);
            ShowWindow(nuevaVentana, SW_SHOW);
            EndDialog(hWnd, 0);
            ventanaPrincipal = nuevaVentana;
        }break;
        }
    }break;
    }
    return FALSE;
}
LRESULT CALLBACK CallbackReportedeVentas(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG:
    case WM_CREATE: {
        return TRUE;
    }break;
    case WM_ACTIVATE: {
        ventanaPrincipal = hWnd;
    }break;
    case WM_COMMAND: {
        int opcion = LOWORD(wParam);
        if (menuOpciones(hWnd, opcion))
            return FALSE;
        switch (opcion) {
        }
    }break;
    }
    return FALSE;
}
//YA ESTA TERMINADO
bool menuOpciones(HWND ventana, int opciones) {
    switch (opciones) {
    case ID_nuevoEmpleado: {
        /* if (usuarioLoggeado != "admin") {
            MessageBox(ventana, "Solo el Administrador puede registrar un nuevo usuario", "Error", 0);
            break;
        }*/
        HWND nuevaVentana =
            CreateDialog(hInst,
                MAKEINTRESOURCE(IDD_Registro_de_usuario),
                NULL, CallbackRegistrarEmpleado);
        ShowWindow(nuevaVentana, SW_SHOW);
        EndDialog(ventana, 0);
        ventanaPrincipal = nuevaVentana;
    }break;
    case ID_info_del_empleado: {
        HWND nuevaVentana =
            CreateDialog(hInst,
                MAKEINTRESOURCE(IDD_PERFIL_DE_EMPLEADO),
                NULL, CallbackPerfildeEmpleado);
        ShowWindow(nuevaVentana, SW_SHOW);
        EndDialog(ventana, 0);
        ventanaPrincipal = nuevaVentana;
    }break;
    case ID_registro_de_empleados: {
        HWND nuevaVentana =
            CreateDialog(hInst,
                MAKEINTRESOURCE(IDD_REGISTRO_DE_EMPLEADOS),
                NULL, CallbackRegistrodeEmpleados);
        ShowWindow(nuevaVentana, SW_SHOW);
        EndDialog(ventana, 0);
        ventanaPrincipal = nuevaVentana;
    }break;
    case ID_registro_de_salas: {
        HWND nuevaVentana =
            CreateDialog(hInst,
                MAKEINTRESOURCE(IDD_REGISTRO_DE_SALAS),
                NULL, CallbackRegistrodeSalas);
        ShowWindow(nuevaVentana, SW_SHOW);
        EndDialog(ventana, 0);
        ventanaPrincipal = nuevaVentana;
    }break;
    case ID_registrar_funciones: {
        HWND nuevaVentana =
            CreateDialog(hInst,
                MAKEINTRESOURCE(IDD_REGISTRO_DE_FUNCIONES),
                NULL, CallbackRegistrodeFunciones);
        ShowWindow(nuevaVentana, SW_SHOW);
        EndDialog(ventana, 0);
        ventanaPrincipal = nuevaVentana;
    }break;
    case ID_registro_de_funciones: {
        HWND nuevaVentana =
            CreateDialog(hInst,
                MAKEINTRESOURCE(IDD_FUNCIONES_REGISTRADAS),
                NULL, CallbackFuncionesRegistradas);
        ShowWindow(nuevaVentana, SW_SHOW);
        EndDialog(ventana, 0);
        ventanaPrincipal = nuevaVentana;
    }break;
    case ID_venta_de_boletos: {
        HWND nuevaVentana =
            CreateDialog(hInst,
                MAKEINTRESOURCE(IDD_Venta_de_boletos),
                NULL, CallbackVentanaPrincipal);
        ShowWindow(nuevaVentana, SW_SHOW);
        EndDialog(ventana, 0);
        ventanaPrincipal = nuevaVentana;
    }break;
    case ID_reporte_de_ventas: {
        HWND nuevaVentana =
            CreateDialog(hInst,
                MAKEINTRESOURCE(IDD_REPORTE_DE_VENTAS),
                NULL, CallbackReportedeVentas);
        ShowWindow(nuevaVentana, SW_SHOW);
        EndDialog(ventana, 0);
        ventanaPrincipal = nuevaVentana;
    }break;
    case WM_DESTROY:
    case WM_CLOSE:
    case ID_SALIR: {
        EndDialog(ventana, 0);
        ventanaPrincipal = NULL;
    }break;
    default: return false;
    }
    return true;
}

NODOEMPLEADO* crearNodoEmpleado(string nombre, string rfc, string usuario, string password, string imagen) {
    NODOEMPLEADO* nuevo = new NODOEMPLEADO;
    if (nuevo == NULL) return NULL;
    strcpy_s(nuevo->empleado.nombre, 255, nombre.c_str());
    strcpy_s(nuevo->empleado.rfc, 15, rfc.c_str());
    strcpy_s(nuevo->empleado.usuario, 100, usuario.c_str());
    strcpy_s(nuevo->empleado.password, 100, password.c_str());
    strcpy_s(nuevo->empleado.imagen, 255, imagen.c_str());
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

bool agregarEmpleadoAlFinal(NODOEMPLEADO* empleado) {
    if (origenEmpleado == NULL) {
        origenEmpleado = empleado;
        finalEmpleado = empleado;
    }
    else {
        finalEmpleado->siguiente = empleado;
        empleado->anterior = finalEmpleado;
        finalEmpleado = empleado;
    }
    return true;
}

NODOEMPLEADO* buscarEmpleadoPorNombre(
    string nombre) {
    NODOEMPLEADO* indice = origenEmpleado;
    while (indice != NULL) {
        if (strcmp(indice->empleado.nombre,
            nombre.c_str()) == 0) {
            break;
        }
        indice = indice->siguiente;
    }
    return indice;
}
NODOEMPLEADO* buscarEmpleadoPorUsuario(
    string usuario) {
    NODOEMPLEADO* indice = origenEmpleado;
    while (indice != NULL) {
        if (strcmp(indice->empleado.usuario, usuario.c_str()) == 0) {
            break;
        }
        indice = indice->siguiente;
    }
    return indice;
}

bool eliminarEmpleadoAlInicio() {
    if (origenEmpleado == NULL) return true;
    if (origenEmpleado == finalEmpleado)
        finalEmpleado = NULL;
    NODOEMPLEADO* aux = origenEmpleado;
    origenEmpleado = origenEmpleado->siguiente;
    if (origenEmpleado != NULL)
        origenEmpleado->anterior = NULL;
    delete aux;
    return true;
}

bool eliminarEmpleadoAlFinal() {
    if (finalEmpleado == NULL) return true;
    if (finalEmpleado == origenEmpleado)
        origenEmpleado = NULL;
    NODOEMPLEADO* aux = finalEmpleado;
    finalEmpleado = finalEmpleado->anterior;
    if (finalEmpleado != NULL)
        finalEmpleado->siguiente = NULL;
    delete aux;
    return true;
}

bool eliminarEmpleadoAlMedio(string nombre) {
    NODOEMPLEADO* busqueda =
        buscarEmpleadoPorNombre(nombre);
    if (busqueda == NULL) return false;
    NODOEMPLEADO* siguiente = busqueda->siguiente,
        * anterior = busqueda->anterior;
    if (anterior == NULL)
        return eliminarEmpleadoAlInicio();
    if (siguiente == NULL)
        return eliminarEmpleadoAlFinal();
    anterior->siguiente = siguiente;
    siguiente->anterior = anterior;
    delete busqueda;
    return true;
}
void imprimirLista() {
    NODOEMPLEADO* indice = origenEmpleado;
    while (indice != NULL) {
        indice = indice->siguiente;
    }
}

void guardarArchivoEmpleados() {
    fstream archivo("C:\\Users\\PC\\\Downloads\\\PIA_Equipo_5",
        ios::binary |
        ios::trunc |
        ios::out);
    if (!archivo.is_open())
        return;
    NODOEMPLEADO* indice = origenEmpleado;
    while (indice != NULL) {
        archivo.write((char*)indice,
            sizeof(NODOEMPLEADO));
        indice = indice->siguiente;
    }
    archivo.close();
}

void leerArchivoEmpleados() {
    fstream archivo("C:\\Users\\PC\\\Downloads\\\PIA_Equipo_5",
        ios::ate |
        ios::in |
        ios::binary);
    if (!archivo.is_open())
        return;
    long tamanio = archivo.tellg();
    archivo.seekg(ios::beg);
    long bytes = 0;
    while (bytes < tamanio) {
        NODOEMPLEADO temp;
        archivo.read((char*)&temp,
            sizeof(NODOEMPLEADO));
        NODOEMPLEADO* nuevo =
            crearNodoEmpleado(temp.empleado.nombre,
                temp.empleado.rfc, temp.empleado.usuario, temp.empleado.password, temp.empleado.password);
        agregarEmpleadoAlFinal(nuevo);
        bytes = bytes + sizeof(NODOEMPLEADO);
    }
    archivo.close();
}

wstring s2ws(const std::string& s, bool isUtf8) {
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(isUtf8 ? CP_UTF8 : CP_ACP, 0, s.c_str(), slength, 0, 0);
    std::wstring buf;
    buf.resize(len);
    MultiByteToWideChar(isUtf8 ? CP_UTF8 : CP_ACP, 0, s.c_str(), slength,
        const_cast<wchar_t*>(buf.c_str()), len);
    return buf;
}
NODOSALAS* crearNodoSala(int númeroDeSala, int númeroDeAsientos)
{
    NODOSALAS* nuevo = new NODOSALAS;
    if (nuevo == NULL) return NULL;
    nuevo->salas.númeroDeSala = númeroDeSala;
    nuevo->salas.númeroDeAsientos = númeroDeAsientos;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

bool agregarSalaAlFinal(NODOSALAS* salas)
{
    if (primeraSala == NULL) {
        primeraSala = salas;
        últimaSala = salas;
    }
    else {
        últimaSala->siguiente = salas;
        salas->anterior = últimaSala;
        últimaSala = salas;
    }
    return true;
}

/*NODOSALAS* buscarSalaPorNúmeroDeSala(int númeroDeSala)
{
    NODOSALAS* indice = primeraSala;
    while (indice != NULL) {
        if (strcmp(indice->salas.númeroDeSala,
            númeroDeSala.c_str()) == 0) {
            break;
        }
        indice = indice->siguiente;
    }
    return indice;
}*/

void imprimirListaSalas() {
    NODOSALAS* indice = primeraSala;
    while (indice != NULL) {
        indice = indice->siguiente;
    }
}

void guardarArchivoSalas() {
    fstream archivo("C:\\Users\\PC\\\Downloads\\\PIA_Equipo_5",
        ios::binary |
        ios::trunc |
        ios::out);
    if (!archivo.is_open())
        return;
    NODOSALAS* indice = primeraSala;
    while (indice != NULL) {
        archivo.write((char*)indice,
            sizeof(NODOSALAS));
        indice = indice->siguiente;
    }
    archivo.close();
}

void leerArchivoSalas() {
    fstream archivo("C:\\Users\\PC\\\Downloads\\\PIA_Equipo_5",
        ios::ate |
        ios::in |
        ios::binary);
    if (!archivo.is_open())
        return;
    long tamanio = archivo.tellg();
    archivo.seekg(ios::beg);
    long bytes = 0;
    while (bytes < tamanio) {
        NODOSALAS temp;
        archivo.read((char*)&temp,
            sizeof(NODOSALAS));
        NODOSALAS* nuevo =
            crearNodoSala(temp.salas.númeroDeSala, temp.salas.númeroDeAsientos);
        agregarSalaAlFinal(nuevo);
        bytes = bytes + sizeof(NODOSALAS);
    }
    archivo.close();
}
NODOFUNCIONES* crearNodoFunciones(string nombreDePelícula, int duración, string clasificación, string idioma, int númeroDeSala, int númeroDeAsientos,
    string fechaDeInicio, string fechaDeFin, int hora, int precio, string imagen) {
    NODOFUNCIONES* nuevo = new NODOFUNCIONES;
    if (nuevo == NULL) return NULL;
    strcpy_s(nuevo->funciones.nombreDePelícula, 255, nombreDePelícula.c_str());
    nuevo->funciones.duración = duración;
    strcpy_s(nuevo->funciones.clasificación, 1, clasificación.c_str());
    strcpy_s(nuevo->funciones.idioma, 255, idioma.c_str());
    nuevo->funciones.númeroDeSala = númeroDeSala;
    nuevo->funciones.númeroDeAsientos = númeroDeAsientos;
    strcpy_s(nuevo->funciones.fechaDeInicio, 100, fechaDeInicio.c_str());
    strcpy_s(nuevo->funciones.fechaDeFin, 100, fechaDeFin.c_str());
    nuevo->funciones.hora = hora;
    nuevo->funciones.precio = precio;
    strcpy_s(nuevo->funciones.imagen, 255, imagen.c_str());
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

bool agregarFuncionAlFinal(NODOFUNCIONES* funciones)
{
    if (primeraFunción == NULL) {
        primeraFunción = funciones;
        últimaFunción = funciones;
    }
    else {
        últimaFunción->siguiente = funciones;
        funciones->anterior = últimaFunción;
        últimaFunción = funciones;
    }
    return true;
}

NODOFUNCIONES* buscarFunciónPorNombreDePelícula(string nombreDePelícula)
{
    NODOFUNCIONES* indice = primeraFunción;
    while (indice != NULL) {
        if (strcmp(indice->funciones.nombreDePelícula,
            nombreDePelícula.c_str()) == 0) {
            break;
        }
        indice = indice->siguiente;
    }
    return indice;
}

bool eliminarFunciónAlInicio() {
    if (primeraFunción == NULL) return true;
    if (primeraFunción == últimaFunción)
        últimaFunción = NULL;
    NODOFUNCIONES* aux = primeraFunción;
    primeraFunción = primeraFunción->siguiente;
    if (primeraFunción != NULL)
        primeraFunción->anterior = NULL;
    delete aux;
    return true;
}

bool eliminarFunciónAlFinal() {
    if (últimaFunción == NULL) return true;
    if (últimaFunción == primeraFunción)
        primeraFunción = NULL;
    NODOFUNCIONES* aux = últimaFunción;
    últimaFunción = últimaFunción->anterior;
    if (últimaFunción != NULL)
        últimaFunción->siguiente = NULL;
    delete aux;
    return true;
}

bool eliminarFunciónAlMedio(string nombreDePelícula) {
    NODOFUNCIONES* busqueda =
        buscarFunciónPorNombreDePelícula(nombreDePelícula);
    if (busqueda == NULL) return false;
    NODOFUNCIONES* siguiente = busqueda->siguiente,
        * anterior = busqueda->anterior;
    if (anterior == NULL)
        return eliminarFunciónAlInicio();
    if (siguiente == NULL)
        return eliminarFunciónAlFinal();
    anterior->siguiente = siguiente;
    siguiente->anterior = anterior;
    delete busqueda;
    return true;
}
void imprimirListaFunciones() {
    NODOFUNCIONES* indice = primeraFunción;
    while (indice != NULL) {
        indice = indice->siguiente;
    }
}

void guardarArchivoFunciones() {
    fstream archivo("C:\\Users\\PC\\\Downloads\\\PIA_Equipo_5",
        ios::binary |
        ios::trunc |
        ios::out);
    if (!archivo.is_open())
        return;
    NODOFUNCIONES* indice = primeraFunción;
    while (indice != NULL) {
        archivo.write((char*)indice,
            sizeof(NODOFUNCIONES));
        indice = indice->siguiente;
    }
    archivo.close();
}

void leerArchivoFunciones() {
    fstream archivo("C:\\Users\\PC\\\Downloads\\\PIA_Equipo_5",
        ios::ate |
        ios::in |
        ios::binary);
    if (!archivo.is_open())
        return;
    long tamanio = archivo.tellg();
    archivo.seekg(ios::beg);
    long bytes = 0;
    while (bytes < tamanio) {
        NODOFUNCIONES temp;
        archivo.read((char*)&temp,
            sizeof(NODOFUNCIONES));
        NODOFUNCIONES* nuevo = crearNodoFunciones(temp.funciones.nombreDePelícula, temp.funciones.duración, temp.funciones.clasificación, temp.funciones.idioma, temp.funciones.númeroDeSala, temp.funciones.númeroDeAsientos, temp.funciones.fechaDeInicio, temp.funciones.fechaDeFin, temp.funciones.hora, temp.funciones.precio, temp.funciones.imagen);
        agregarFuncionAlFinal(nuevo);
        bytes = bytes + sizeof(NODOFUNCIONES);
    }
    archivo.close();
}

/*NODOVENTAS* crearNodoVentas(string formaDePago, string fecha, int boletos, int precio)
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string fecha = std::to_string(1 + ltm->tm_mon) + "/" + std::to_string(ltm->tm_mday) + "/" + std::to_string(1900 + ltm->tm_year);
    NODOVENTAS* nuevo = new NODOVENTAS;
    if (nuevo == NULL) return NULL;
    strcpy_s(nuevo->ventas.formaDePago, 100,
        formaDePago.c_str());
    nuevo->ventas.boletos = boletos;
    nuevo->ventas.precio = precio;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

bool agregarVentaAlFinal(NODOVENTAS* ventas)
{
    if (primeraVenta == NULL) {
        primeraVenta = ventas;
        últimaVenta = ventas;
    }
    else {
        últimaVenta->siguiente = ventas;
        ventas->anterior = últimaVenta;
        últimaVenta = ventas;
    }
    return true;
}

NODOVENTAS* buscarFuncionPorPagoYFecha(string formaDePago, string fecha)
{
    NODOVENTAS* indice = primeraVenta;
    while (indice != NULL) {
        if (strcmp(indice->ventas.formaDePago,
            formaDePago.c_str()) == 0) {
            break;
        }
        if (strcmp(indice->ventas.fecha,
            fecha.c_str()) == 0) {
            break;
        }

        indice = indice->siguiente;
    }
    return indice;
}

void imprimirListaVentas() {
    NODOVENTAS* indice = primeraVenta;
    while (indice != NULL) {
        indice = indice->siguiente;
    }
}

void guardarArchivoVentas() {
    fstream archivo("C:\\Users\\PC\\\Downloads\\\PIA_Equipo_5",
        ios::binary |
        ios::trunc |
        ios::out);
    if (!archivo.is_open())
        return;
    NODOVENTAS* indice = primeraVenta;
    while (indice != NULL) {
        archivo.write((char*)indice,
            sizeof(NODOVENTAS));
        indice = indice->siguiente;
    }
    archivo.close();
}

void leerArchivoVentas() {
    fstream archivo("C:\\Users\\PC\\\Downloads\\\PIA_Equipo_5",
        ios::ate |
        ios::in |
        ios::binary);
    if (!archivo.is_open())
        return;
    long tamanio = archivo.tellg();
    archivo.seekg(ios::beg);
    long bytes = 0;
    while (bytes < tamanio) {
        NODOVENTAS temp;
        archivo.read((char*)&temp,
            sizeof(NODOVENTAS));
        NODOVENTAS* nuevo = crearNodoVentas(temp.ventas.formaDePago, temp.ventas.fecha, temp.ventas.boletos, temp.ventas.precio);
        agregarVentaAlFinal(nuevo);
        bytes = bytes + sizeof(NODOVENTAS);
    }
    archivo.close();
}*/