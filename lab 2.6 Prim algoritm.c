#include<windows.h>
#include<math.h>

double* createArray(int n)
{
    double** matrix = (double*)malloc(n * sizeof(double*));

    return matrix;
}

double* create_array(int n)
{
    double* matrix = (double*)malloc(n * sizeof(double*));
    return matrix;
}

int* create_arrayI(int n)
{
    int* matrix = (int*)malloc(n * sizeof(int*));
    return matrix;
}


double** createMatrix(int n)
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

double** rewriteMatrix(double num, double **matrix, int n)
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
double** createNullMatrix(int n)
{
    double** matrix = (double**)malloc(n * sizeof(double*));

    for (int i = 0; i < n; i++)
        matrix[i] = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;
    }

    return matrix;
}

double** roundm (double** m, int n){
    double** matrix = createNullMatrix(n);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            double value = m[i][j];
            matrix[i][j] = round(value);
        }
    }

    return matrix;
}

double** mulm (double** m, int n, int k){
    double** matrix = createNullMatrix(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            double value = m[i][j];
            matrix[i][j] = value * k;
        }
    }

    return matrix;
}

double** mulTwoMatrix(double** M1, double** M2, int n){
    double** matrix = createNullMatrix(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            double value = M1[i][j] * M2[i][j];
            matrix[i][j] = value;
        }
    }

    return matrix;
}

double** plusTwoMatrix(double** M1, double** M2, int n){
    double** matrix = createNullMatrix(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            double value = M1[i][j] + M2[i][j];
            matrix[i][j] = value;
        }
    }

    return matrix;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char ProgName[] = "Lab work 5";

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
        "Lab work 5. Zinovij Bogdan",
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        1100,
        750,
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
        MoveToEx(hdc, nx[i]-15*cos(fi), ny[i]-15*sin(fi), NULL);
        LineTo(hdc, nx[j]+15*cos(fi), ny[j]+15*sin(fi));
    }

    void shiftedLine(double* nx, double* ny, int i, int j, double fi)
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

    void bentLine(double* nx, double* ny, int i, int j, double fi, int centreX, int centreY)
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
    }

    double getFi(double* nx, double* ny, int i, int j)
    {
        double fi = 3.1416 + acos((nx[j]-nx[i]) / (sqrt(pow(nx[j]-nx[i], 2) + pow(ny[j]-ny[i], 2))));
        if(ny[j] < ny[i]) fi *= -1;

        return fi;
    }

    void printMatrix(double** A, int n)
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

    void printMatrix1(double** A, int n)
    {
        for (int i = 0; i < n; i++)
            {
            for (int j = 0; j < n; j++)
            {
                printf(" %.0lf,", A[i][j]);
                if(A[i][j] > 9 && A[i][j] < 100){
                    printf(" ");
                }
                if(A[i][j] < 10){
                    printf("  ");
                }
            }
            printf("\n");
        }
    }

    switch(messg){
        case WM_PAINT :

            hdc=BeginPaint(hWnd, &ps);
            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
            HPEN GPen = CreatePen(PS_SOLID, 2, RGB(20, 205, 20));
            HPEN RPen = CreatePen(PS_SOLID, 2, RGB(205, 20, 20));

            int n = 10;
            int radius = 300;
            int centreX = 350;
            int centreY = 350;
            int dx = 16, dy = 16, dtx = 5;
            double k = 2 * 3.1416 / (n-1);
            char* numbers[20] = {"1","2","3","4","5","6","7","8","9","10",
                       "11","12","13","14","15","16","17","18","19","20"};
            double* nx = createArray(n);
            double* ny = createArray(n);

            for (int i = 0; i < n-1; i++){
                nx[i] = centreX + radius * cos(k*i);
                ny[i] = centreY - radius * sin(k*i);
            }
            nx[n-1] = centreX;
            ny[n-1] = centreY;

                srand(0407);

//---------------------------------------------Martix Weight and Adjacency-------------------------------
    double num = 1.0 - 0*0.1 - 7*0.005 - 0.05;
    double** T = createMatrix(n);
    double** A = rewriteMatrix(num, T, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(A[i][j] > 0){
                A[j][i] = A[i][j];
            }
        }
    }

    double** M = createMatrix(n); // for WT1
    double** rand = mulm(M, n, 100);
    double** M2 = mulTwoMatrix(rand, A, n);
    double** Wt = roundm(M2, n);

    //B
    double** B = createNullMatrix(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(Wt[i][j] == 0){
                B[i][j] = 0;
            } else {
                B[i][j] = 1;
            }
        }
    }

    //C
    double** C = createNullMatrix(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(B[i][j] != B[j][i]){
                C[i][j] = 1;
            } else {
                C[i][j] = 0;
            }
        }
    }

    //D
    double** D = createNullMatrix(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(B[i][j] == B[j][i] && B[i][j] == 1){
                D[i][j] = 1;
            } else {
                D[i][j] = 0;
            }
        }
    }

    // D*Tr
    for (int i = 0; i < n-1; i++){
        for (int j = i+1; j < n; j++){
            D[i][j] = 0;
        }
    }

    //C+D
    double** M3 = plusTwoMatrix(D, C, n);
    double** WT = mulTwoMatrix(M3, Wt, n);

    // make symetrical
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(WT[i][j] > 0){
                WT[j][i] = WT[i][j];
            }
        }
    }

            printf("\n Matrix of adjacency: \n");
            printMatrix(A, n);

//-----------------------------------Draw graph-----------------------------------------------------

            SelectObject(hdc, KPen);
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (A[i][j] == 1){
                        if (A[i][j] == 1 && i == j){
                            loop(nx, ny, i, j, centreX, centreY);
                        } else {
                            double fi = getFi(nx, ny, i, j);
                            line(nx, ny, i, j, fi);
                            char* nn = malloc(3 * sizeof(char*));
                            sprintf(nn, "%0.lf", WT[i][j]);
                            TextOut(hdc, (nx[i] + nx[j]) * 0.5-9, (ny[i] + ny[j]) * 0.5-9, nn, 3);
                            free(nn);
                        }
                        
                    }
                }
            }

            SelectObject(hdc, BPen);
            for(int i = 0; i < n; i++){
                Ellipse(hdc, nx[i]-dx, ny[i]-dy, nx[i]+dx, ny[i]+dy);
                TextOut(hdc, nx[i]-dtx, ny[i]-dy/2, numbers[i], 2);
            }
            TextOut(hdc, nx[9]-dtx, ny[9]-dy/2, numbers[9], 2);

//--------------------------------------Functions for select new actiw vertices and search minimal weight-----------

            int isNoNewVetices(int n, double* DFS){
                int counter = 0;
                for(int i = 0; i < n; i++){
                    if(DFS[i] > 0){
                        counter++;
                    }
                }

                if(counter > 9.5){
                    return 1;
                } else {
                    return 0;
                }
            }

            int searchMinWeight(int activV, int n, double* vertices, double** A, double** WT){
                int value = -1;
                int* freeVert = create_arrayI(n); 
                int count = 0;
                for(int i =0; i<n; i++){
                    if (vertices[i]==0 && A[activV][i] != 0){
                        freeVert[count] = i;
                        count++;
                    }
                }

                value = freeVert[0];
                for(int i = 1; i < count; i++){
                    if(WT[activV][freeVert[i]] < WT[activV][value]){
                        value = freeVert[i];
                    } 
                }

                if(vertices[value] != 0){
                    value = -1;
                }

                return value;
            }

            int searchNewActive(int n, double* vertices, double** WT){
                int value;
                int* visitedVert = create_arrayI(n);
                int* minValue = create_arrayI(n);
                int count = 0;
                for(int i =0; i<n; i++){
                    if (vertices[i]!=0){
                        visitedVert[count] = i;
                        count++;
                        
                    }
                }
                int minWeigthOfCurrentVert;
                for(int i = 0; i < count; i++){
                    minWeigthOfCurrentVert = searchMinWeight(visitedVert[i], n, vertices, A, WT);
                    if(minWeigthOfCurrentVert != -1){
                        minValue[i] = WT[visitedVert[i]][minWeigthOfCurrentVert];
                    } else {
                        minValue[i] = -1;
                    }
                }

                value = visitedVert[0];
                int weight = 201;
                for(int i = 0; i < count; i++){
                    if(minValue[i] < weight && minValue[i] > 0){
                        value = visitedVert[i];
                        weight = minValue[i];
                    }
                }

                return value;
            }
// array of vertices, where index == number vertice, if value == 0 => vertice is NEW
            double* vertices = create_array(n);
            for(int i = 0; i < n; i++){
                vertices[i] = 0;
            }

// Derevo obhodu
            double** tree = createMatrix(n);
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    tree[i][j] = 0;
                }
            }

//====================================================================================================
            // Start Prim`s algoritm
            printf("\n Matrix of weight: \n");
            printMatrix1(WT, n);
            int v=1; // activna vert
            vertices[v-1] = 1;
            int count = 1;
            int checkEmpty = 0;
            int q; // doslidzhuvana vert

            int prevV = v; // for drawing
            while (!checkEmpty){
                sleep(2);

                // select new vertice, which is not new and have minimal weight path to new vertice 
                v = searchNewActive(n, vertices, WT);

                q = searchMinWeight(v, n, vertices, A, WT); // new vertice with minimal weight path
                if (q > 0){
                        count++;
                        vertices[q] = count;

                        SelectObject(hdc, GPen);
                        int i = v;
                        int j = q;
                        tree[i][j] = 1;
                        double fi = getFi(nx, ny, i, j);
                        line(nx, ny, i, j, fi);
                        arrow(fi, nx[j], ny[j]);
                        TextOut(hdc, nx[j]-dtx+20, ny[j]-dy/3, numbers[count-1], 2);
                        char* nn = malloc(3 * sizeof(char*));
                        sprintf(nn, "%0.lf", WT[i][j]);
                        TextOut(hdc, (nx[i] + nx[j]) * 0.5-9, (ny[i] + ny[j]) * 0.5-9, nn, 3);
                        free(nn);  
                }
                checkEmpty = isNoNewVetices(n, vertices);
            }

            sleep(2);
//============================================================================================================

// Print and draw minimum spanning tree
            printf("\n Matrix of minimum spanning tree: \n");
            printMatrix(tree, n);

            radius = 130;
            centreX = 900;
            centreY = 350;
            double* nx2 = createArray(n);
            double* ny2 = createArray(n);

            for (int i = 0; i < n-1; i++){
                nx2[i] = centreX + radius * cos(k*i);
                ny2[i] = centreY - radius * sin(k*i);
            }
            nx2[n-1] = centreX;
            ny2[n-1] = centreY;

            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (tree[i][j] == 1){
                        SelectObject(hdc, GPen);
                        double fi = getFi(nx2, ny2, i, j);
                        line(nx2, ny2, i, j, fi);
                        arrow(fi, nx2[j], ny2[j]);
                        char* nn = malloc(3 * sizeof(char*));
                        sprintf(nn, "%0.lf", WT[i][j]);
                        free(nn);
                    }
                }
            }

            SelectObject(hdc, BPen);
            for(int i = 0; i < n; i++){
                Ellipse(hdc, nx2[i]-dx, ny2[i]-dy, nx2[i]+dx, ny2[i]+dy);
                TextOut(hdc, nx2[i]-dtx, ny2[i]-dy/2, numbers[i], 2);
            }

            printf("\n");
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    //
    return 0;
}
