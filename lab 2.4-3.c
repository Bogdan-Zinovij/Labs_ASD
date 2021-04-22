#include<windows.h>
#include<math.h>

double* create_array(int n)
{
    double* array = (double*)malloc(n * sizeof(double*));
    return array;
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

double** create_null_matrix(int n)
{
    double** matrix = (double**)malloc(n * sizeof(double*));

    for (int i = 0; i < n; i++)
        matrix[i] = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            matrix[i][j] =  0;
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

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char ProgName[] = "Lab work 4";

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
        "Lab work 4. Zinovij Bogdan",
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

    void arrow(double fi, double px, double py)
    {
        px += 15*cos(fi);
        py += 15*sin(fi);
        double lx = px+15*cos(fi+0.3);
        double rx = px+15*cos(fi-0.3);
        double ly = py+15*sin(fi+0.3);
        double ry = py+15*sin(fi-0.3);

        MoveToEx(hdc, lx, ly, NULL);
        LineTo(hdc, px, py);
        LineTo(hdc, rx, ry);
    }

    void line(double* nx, double* ny, int i, int j, double fi)
    {
        MoveToEx(hdc, nx[i], ny[i], NULL);
        LineTo(hdc, nx[j], ny[j]);
        arrow(fi, nx[j], ny[j]);
    }

    void shifted_line(double* nx, double* ny, int i, int j, double fi)
    {
        int rad = 16;
        double px1 = nx[i] - rad * cos(fi-3.1416/10);
        double py1 = ny[i] - rad * sin(fi-3.1416/10);
        double px2 = nx[j] + rad * cos(fi+3.1416/10);
        double py2 = ny[j] + rad * sin(fi+3.1416/10);

        MoveToEx(hdc, px1, py1, NULL);
        LineTo(hdc, px2, py2);
        arrow(fi, px2-15*cos(fi), py2-15*sin(fi));
    }

    void bent_line(double* nx, double* ny, int i, int j, double fi, int centreX, int centreY)
    {
        int radius2 = 50;
        double pointX = centreX+radius2 * cos(fi+3.1416/2);
        double pointY = centreY+radius2 * sin(fi+3.1416/2);

        MoveToEx(hdc, nx[i], ny[i], NULL);
        LineTo(hdc, pointX, pointY);
        LineTo(hdc, nx[j], ny[j]);

        fi = 3.1416 + acos((nx[j]-pointX)/(sqrt(pow(nx[j]-pointX, 2) + pow(ny[j]-pointY, 2))));
        if(ny[j] < pointY) fi *= -1;

        arrow(fi, nx[j], ny[j]);
    }

    void loop(double* nx, double* ny, int i, int j, int centreX, int centreY)
    {
        int znakX = 1;
        int znakY = 1;
        if (nx[i] - centreX <= 0) znakX = -1;
        if (ny[i] - centreY <= 0) znakY = -1;

        Arc (hdc, nx[i], ny[i], nx[j]+znakX*40, ny[j]+znakY*40, nx[i], ny[i], nx[j], ny[j]);

        if (znakX == 1 && znakY == -1) arrow(0, nx[j], ny[j]-2);
        if (znakX == -1 && znakY == -1) arrow(3.1416*1.5, nx[j]-2, ny[j]);
        if (znakX == -1 && znakY == 1) arrow(3.1416, nx[j], ny[j]+1);
        if (znakX == 1 && znakY == 1) arrow(3.1416*0.5, nx[j]+1, ny[j]);
    }

    double get_fi(double* nx, double* ny, int i, int j)
    {
        double fi = 3.1416 + acos((nx[j]-nx[i]) / (sqrt(pow(nx[j]-nx[i], 2) + pow(ny[j]-ny[i], 2))));
        if(ny[j] < ny[i]) fi *= -1;

        return fi;
    }

    void print_matrix(double** A, int n)
    {
        for (int i = 0; i < n; i++)
            {
            for (int j = 0; j < n; j++)
            {
                printf(" %.0lf,", A[i][j]);
            }
            printf("\n");
        }
    }

    //друк матриці певного степеня
    void print_matrix_deg(double*** M, int n, int deg){
        printf("\n Matrix in degree %d :\n", deg);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                printf(" %0.lf,", M[deg-1][i][j]);
            }
            printf("\n");
        }
    }

    //друк шляхів довжиною 2
    void print_way_two(double*** M, int n){
        printf("\n Paths of length 2 :\n");
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(M[0][i][j] == 1){
                    for(int k = 0; k < n; k++){
                        if(M[0][j][k] == 1) printf("   %d->%d->%d,", i+1, j+1, k+1);
                    }
                }
            }
            printf("\n");
        }
    }

    //друк шляхів довжиною 3
    void print_way_three(double*** M, int n){
        printf("\n");
        printf("\n Paths of length 3 :\n");
        for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(M[0][i][j] == 1){
                        for(int k = 0; k < n; k++){
                            if(M[0][j][k] == 1){
                                for(int f = 0; f < n; f++){
                                    if(M[0][k][f] == 1) printf("   %d->%d->%d->%d,", i+1, j+1, k+1, f+1);
                                }
                            }
                        }
                    }
                }
                printf("\n");
        }
    }

    //порівняння рядочків матриці
    int compar_row(double** M, int n, int n1, int n2){
        int counter = 0;
        for(int i = 0; i < n; i++){
            if(M[n1][i] != M[n2][i]) counter++;
        }

        if(counter >= 1){
            return 0;
        } else {
            return 1;
        }
    }

    double** create_reach_matrix(double*** arr_of_matrix, int n){
        double** reach_matrix = create_null_matrix(n);

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                for(int k =0; k < n-1; k++){
                    reach_matrix[i][j] += arr_of_matrix[k][i][j];
                }
            }
        }
        for(int i = 0; i < n; i++){
            for(int j =0; j < n; j++){
                if(reach_matrix[i][j] >= 1){
                    reach_matrix[i][j] = 1;
                }
            }
            reach_matrix[i][i] = 1;
        }

        return reach_matrix;
    }

    double** create_connect_matrix(double** reach_matrix, int n){
        double** connect_matrix = create_null_matrix(n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(reach_matrix[i][j] == 1 && reach_matrix[j][i] == 1){
                    connect_matrix[i][j] = 1;
                }
            }
        }
        return connect_matrix;
    }

    switch(messg){
        case WM_PAINT :

            hdc=BeginPaint(hWnd, &ps);
            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

            int n = 10;//drawing graph
            int radius = 300;
            int centreX = 400;
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
            double num = 1.0-0*0.005-7*0.005-0.27;
            double** A = rewrite_matrix(num, T, n);

            printf(" The matrix of adjacency %d * %d:\n", n, n);
            print_matrix(A, n);

            //друк напівстепенів
            double* degPlus = create_array(n);
            double* degMinus = create_array(n);
            for(int i = 0; i < n; i++){
                degPlus[i] = 0;
                degMinus[i] = 0;
            }


            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(A[i][j] == 1) degPlus[i] += 1;
                    if(A[j][i] == 1) degMinus[i] += 1;
                }
            }

            printf("\n Deg+ and Deg- :\n\n");
            for(int i = 0; i < n; i++){
                printf(" Vertex number: %d", i+1);
                printf("    deg+ = %0.lf", degPlus[i]);
                printf("    deg- = %0.lf\n", degMinus[i]);
            }

            //створення масиву з двовимірних матриць
            double** arr_of_matrix[9];
            for (int i = 0; i < n; i++) {
                arr_of_matrix[i] = create_null_matrix(n);
            }
            arr_of_matrix[0] = A;

            //послідовне перезаписування нульових матриць в матриці певного степеню
            for(int k = 1; k < n-1; k++){
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < n; j++){
                        if(arr_of_matrix[k-1][i][j] == 1){
                            for(int f = 0; f < n; f++){
                                if(arr_of_matrix[0][j][f] == 1) arr_of_matrix[k][i][f] = 1;
                            }
                        }
                    }
                }
            }

            //друк шляхів
            print_matrix_deg(arr_of_matrix, n, 2);
            print_way_two(arr_of_matrix, n);

            print_matrix_deg(arr_of_matrix, n, 3);
            print_way_three(arr_of_matrix, n);

            //створення і заповнення матриці досяжності

            double** reach_matrix = create_reach_matrix(arr_of_matrix, n);

            printf("\n The reachability matrix :\n");
            print_matrix(reach_matrix, n);


            //матриця звязності
            double** connect_matrix = create_connect_matrix(reach_matrix, n);

            printf("\n The connectivity matrix :\n", n, n);
            print_matrix(connect_matrix, n);

        //друк компонентів сильної звязності
            double* vert_components = create_array(n);
            for(int i = 0; i < n; i++){
                vert_components[i] = 0;
            }

            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(i != j && compar_row(connect_matrix, n, i, j)){
                        vert_components[i] = 1;
                        vert_components[j] = 1;
                    }
                }
            }

            double* vert_components1 = create_array(n);
            for(int i = 0; i < n; i++){
                vert_components1[i] = vert_components[i];
            }

            printf("\n Components of strong connectivity : \n");

            double** components = create_null_matrix(n);

            int n_components = 0;
            for(int i = 0; i < n; i++){
                int n_vertices = 0;
                if(vert_components[i] == 1){
                    printf(" K%d: ", n_components+1);
                    for(int j = 0; j < n; j++){
                        if(compar_row(connect_matrix, n, i, j)){
                            if(n_vertices != 0) printf("-");
                            printf(" %d ", j+1);
                            components[n_components][n_vertices] = j+1;
                            vert_components[j] = 0;
                            n_vertices++;
                        }

                    }
                    printf("\n");
                    n_components++;
                }
            }

            for(int i = 0; i < n; i++){
                if(vert_components1[i] == 0) printf(" %d\n", i+1);
            }
//graph condensacii
            double** matrix_of_components = create_null_matrix(n);
            int counter_position = 0;
            for(int i = 0; i < n; i++){
                if(components[i][0] != 0){
                    for(int j = 0; j < n; j++){
                        if(components[i][j] != 0){
                            matrix_of_components[i][j] = components[i][j];
                        }
                    }
                    counter_position ++;
                }
            }
            for(int i = 0; i < n; i++){
                if(vert_components1[i] == 0) {
                matrix_of_components[counter_position][0] = i+1;
                counter_position++;
                }
            }

            int counter_n = 0;
            for(int i = 0; i < n; i++){
                if(matrix_of_components[i][0] != 0){
                    counter_n++;
                }
            }

            double** con_matrix = create_null_matrix(counter_n);
            for(int i = 0; i < counter_n; i++){
                for(int j = 0; j < counter_n; j++){
                    int i1 = matrix_of_components[i][0]-1;
                    for(int k = 0; k < n; k++){
                        if(matrix_of_components[i][k] != 0){
                            int i2 = matrix_of_components[j][k]-1;
                            if(A[i1][i2] == 1){
                                con_matrix[i][k] = 1;
                            }
                        }
                    }
                }
            }
            printf("\n Matrix of condensation :\n");
            print_matrix(con_matrix, counter_n);

            //малювання графу

            SelectObject(hdc, KPen);
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (A[i][j] == 1){
                        if (A[i][j] == 1 && i == j){
                            loop(nx, ny, i, j, centreX, centreY);
                        }
                        double fi = get_fi(nx, ny, i, j);
                        if ((i-j==(n-1)/2 || j-i==(n-1)/2) && i!=n-1 && j!=n-1 && n%2==1){
                            bent_line(nx, ny, i, j, fi, centreX, centreY);
                        } else if (A[i][j] == A[j][i]) {
                            shifted_line(nx, ny, i, j, fi);
                        } else {
                            line(nx, ny, i, j, fi);
                        }
                    }
                }
            }
            SelectObject(hdc, BPen);
            for(int i = 0; i < n; i++){
                Ellipse(hdc, nx[i]-dx, ny[i]-dy, nx[i]+dx, ny[i]+dy);
                TextOut(hdc, nx[i]-dtx, ny[i]-dy/2, numbers[i], 2);
            }

            //draw condence graph

            n = counter_n; // size of condence matrix
            radius = 150;
            centreX = 950;
            centreY = 400;
            dx = 16, dy = 16, dtx = 5;
            k = 2 * 3.1416 / (n-1);
            double* nx2 = create_array(n);
            double* ny2 = create_array(n);

            for (int i = 0; i < n-1; i++){
                nx2[i] = centreX + radius * cos(k*i);
                ny2[i] = centreY - radius * sin(k*i);
            }
            nx2[n-1] = centreX;
            ny2[n-1] = centreY;

            SelectObject(hdc, KPen);
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (con_matrix[i][j] == 1){
                        if (con_matrix[i][j] == 1 && i == j){
                            loop(nx2, ny2, i, j, centreX, centreY);
                        }
                        double fi = get_fi(nx2, ny2, i, j);
                        if ((i-j==(n-1)/2 || j-i==(n-1)/2) && i!=n-1 && j!=n-1 && n%2==1){
                            bent_line(nx2, ny2, i, j, fi, centreX, centreY);
                        } else if (con_matrix[i][j] == con_matrix[j][i]) {
                            shifted_line(nx2, ny2, i, j, fi);
                        } else {
                            line(nx2, ny2, i, j, fi);
                        }
                    }
                }
            }

            char* component_numbers[5] = {"K1","K2","K3","K4","K5"};

            SelectObject(hdc, BPen);
            for(int i = 0; i < n; i++){
                Ellipse(hdc, nx2[i]-dx, ny2[i]-dy, nx2[i]+dx, ny2[i]+dy);
                if(matrix_of_components[i][1] != 0){
                    TextOut(hdc, nx2[i]-dtx, ny2[i]-dy/2, component_numbers[i], 2);
                } else {
                    int index = matrix_of_components[i][0];
                    TextOut(hdc, nx2[i]-dtx, ny2[i]-dy/2, numbers[index-1], 2);
                }
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

