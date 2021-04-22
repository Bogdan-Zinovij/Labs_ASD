#include<windows.h>
#include<math.h>

double* create_array(int n)
{
    double* matrix = (double*)malloc(n * sizeof(double*));
    return matrix;
}

double** create_matrix(int n)
{
    double** matrix = (double**)malloc(n * sizeof(double*));

    for (int i = 0; i < n; i++)
        matrix[i] = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            matrix[i][j] =  2.0 / RAND_MAX * rand();
    }

    return matrix;
}

double** rewrite_matrix(double num, double **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = matrix[i][j] * num;

            if(matrix[i][j] > 1.0)
            {
                matrix[i][j] = 1;
            } else
                matrix[i][j] = 0;
        }
    }

    return matrix;
}

double** make_symmetrical(double **matrix, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(matrix[i][j] != 0)
            matrix[j][i] = 1;
        }
    }

    return matrix;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char ProgName[] = "Lab work 3";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS w;
    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if(!RegisterClass(&w))
        return 0;

    hWnd=CreateWindow(ProgName,
        "Lab work 3. Zinovij Bogdan",
        WS_OVERLAPPEDWINDOW,
        5,
        5,
        1000,
        800,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&lpMsg, hWnd, 0, 0)) {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
    return(lpMsg.wParam);
    }

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    void line(double* nx, double* ny, int i, int j)
    {
        MoveToEx(hdc, nx[i], ny[i], NULL);
        LineTo(hdc, nx[j], ny[j]);
    }

    void bent_line(double* nx, double* ny, int i, int j, double fi, int centreX, int centreY)
    {
        int radius2 = 50;
        double pointX = centreX+radius2 * cos(fi+3.1416/2);
        double pointY = centreY+radius2 * sin(fi+3.1416/2);

        MoveToEx(hdc, nx[i], ny[i], NULL);
        LineTo(hdc, pointX, pointY);
        LineTo(hdc, nx[j], ny[j]);
    }

    void loop(double* nx, double* ny, int i, int j, int centreX, int centreY)
    {
        int znakX = 1;
        int znakY = 1;
        if (nx[i] - centreX <= 0) znakX = -1;
        if (ny[i] - centreY <= 0) znakY = -1;

        Arc (hdc, nx[i], ny[i], nx[j]+znakX*40, ny[j]+znakY*40, nx[i], ny[i], nx[j], ny[j]);
    }

    double get_fi(double* nx, double* ny, int i, int j)
    {
        double fi = 3.1416 + acos((nx[j]-nx[i]) / (sqrt(pow(nx[j]-nx[i], 2) + pow(ny[j]-ny[i], 2))));
        if(ny[j] < ny[i]) fi *= -1;

        return fi;
    }

    void print_matrix(double** A, int n)
    {
        printf(" The matrix %d * %d:\n", n, n);
        for (int i = 0; i < n; i++)
            {
            for (int j = 0; j < n; j++)
            {
                printf("%.0lf, ", A[i][j]);
            }
            printf("\n");
        }
    }

    switch(messg){
        case WM_PAINT :

            hdc=BeginPaint(hWnd, &ps);
            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

            int n = 10;
            int radius = 300;
            int centreX = 500;
            int centreY = 400;
            int dx = 16, dy = 16, dtx = 5;
            double k = 2 * 3.1416 / (n-1);
            char* numbers[20] = {"1","2","3","4","5","6","7","8","9","10",
                       "11","12","13","14","15","16","17","18","19","20"};
            double* nx = create_array(n);
            double* ny = create_array(n);

            for (int i = 0; i < n-1; i++){
                nx[i] = centreX + radius * cos(k*i);
                ny[i] = centreY - radius * sin(k*i);
            }
            nx[n-1] = centreX;
            ny[n-1] = centreY;

            srand(0407);
            double** T = create_matrix(n);
            double num = 1.0-0*0.01-7*0.01-0.3;
            double** A = rewrite_matrix(num, T, n);
            A = make_symmetrical(A, n);

            print_matrix(A, n);

            double* deg = create_array(n);
            for(int i = 0; i < n; i++){
                deg[i] = 0;
            }

            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if(A[i][j] == 1) deg[i]+=1;
                    if(A[i][j] == 1 && i == j) deg[i]+=1;
                }
            }

            printf("\n Deg :\n\n");
            for(int i = 0; i < n; i++){
                printf(" Vertex number: %d", i+1);
                printf("    deg = %0.lf\n", deg[i]);
            }

            printf("\n Hanging vertices:");
            int countVishyachaVerticles = 0;
            for(int i = 0; i < n; i++){
                if(deg[i]==1){
                    printf("  %d", i+1);
                    countVishyachaVerticles += 1;
                }
            }
            if(countVishyachaVerticles == 0) printf("  there are no such vertices!");

            printf("\n Izolated vertices:");
            int countIzoVerticles = 0;
            for(int i = 0; i < n; i++){
                if(deg == 0){
                    printf("  %d", i+1);
                    countIzoVerticles += 1;
                }
            }
            if(countIzoVerticles == 0) printf("  there are no such vertices!");

            int counterDeviations = 0;
            for(int i = 1; i < n; i++){
                if(deg[0] != deg[i]) counterDeviations++;
            }
            if(counterDeviations == 0){
                printf("\n The graph is homogeneous with degree k=%0.lf", deg[0]);
            } else {
                  printf("\n The graph isn`t homogeneous!");
              }

            SelectObject(hdc, KPen);
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (A[i][j] == 1 && i <= j){
                        if (A[i][j] == 1 && i == j){
                            loop(nx, ny, i, j, centreX, centreY);
                        }
                        double fi = get_fi(nx, ny, i, j);
                        if ((i-j==(n-1)/2 || j-i==(n-1)/2) && i!=n-1 && j!=n-1 && n%2==1){
                            bent_line(nx, ny, i, j, fi, centreX, centreY);
                        } else {
                            line(nx, ny, i, j);
                        }
                    }
                }
            }

            SelectObject(hdc, BPen);
            for(int i = 0; i < n; i++){
                Ellipse(hdc, nx[i]-dx, ny[i]-dy, nx[i]+dx, ny[i]+dy);
                TextOut(hdc, nx[i]-dtx, ny[i]-dy/2, numbers[i], 2);
            }

            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
