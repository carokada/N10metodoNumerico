#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

#define N 10

void separacionEnTerminos(string funcionOriginal, vector<string> &funcionEnTerminos);
void imprimirVector(vector<string> vector);
string sumaResta(string termino);
double resolverPotencia(string termino, double valorX);
double resolverMultiplicacion(string termino, double valorX);
double resolverFraccion(string termino, double valorX);
double resolverPolinomio(vector<string> vector, double valorX);
double subintervalos(double limiteA, double limiteB);
void reglaSimpson(double limiteA, double limiteB, double subintervalo, string funcionOriginal, vector<string> funcion);

int main()
{
    string funcion;
    vector<string> funcionEnTerminos;
    double limiteA, limiteB;
    double subintervalo;
    // string polinomio = "12x-6x^5+2x^2-3/4x";

    cout << " ------------------------------------------ " << endl;
    cout << "       programa de metodo numerico " << endl;
    cout << "          regla de simpson 1/3 " << endl;
    cout << " ------------------------------------------ " << endl;
    cout << " operaciones que admite: " << endl;
    cout << " 1. suma (+)" << endl;
    cout << " 2. resta (-)" << endl;
    cout << " 3. multiplicacion (implicita)" << endl;
    cout << " 4. division (/)" << endl;
    cout << " 5. potencia (^) - simbolo '^' = alt + 94" << endl;
    cout << " ------------------------------------------ " << endl;
    cout << " ingrese la funcion a resolver: " << endl;
    cout << " (ejemplo: 12x-6x^5+2x^2-3/4x) " << endl;
    getline(cin, funcion);
    cout << " ingrese el limite a del intervalo: ";
    cin >> limiteA;
    cout << " ingrese el limite b del intervalo: ";
    cin >> limiteB;
    subintervalo = subintervalos(limiteA, limiteB);
    cout << " valor de h (subintervalos) : " << subintervalo << endl;
    cout << " ------------------------------------------ " << endl;
    cout << " separando terminos..." << endl;
    separacionEnTerminos(funcion, funcionEnTerminos);
    cout << " terminos encontrados: " << endl;
    imprimirVector(funcionEnTerminos);
    cout << " ------------------------------------------ " << endl;
    cout << " aplicando metodo de simpson..." << endl;
    reglaSimpson(limiteA, limiteB, subintervalo, funcion, funcionEnTerminos);

    return 0;
}

double subintervalos(double limiteA, double limiteB)
{
    double h = (limiteB - limiteA) / N;
    return h;
}

void separacionEnTerminos(string funcionOriginal, vector<string> &funcionEnTerminos)
{
    string funcion = funcionOriginal;
    int contador = 0;

    for (size_t i = 0; i < funcion.length(); i++)
    {
        string termino = "";
        char caracter = funcion[i];
        // cout << "caracter: " << caracter << endl;

        if (caracter == '+')
        {
            contador++;
            size_t posicionSuma = funcion.find('+');
            // cout << " posicion suma: " << posicionSuma << endl;
            termino = funcion.substr(0, posicionSuma);
            // cout << " termino " << contador << ": " << termino << endl;
            funcionEnTerminos.push_back(termino);
            funcion = funcion.substr(posicionSuma);
            // cout << "funcion restante: " << funcion << endl;
            i = 0;
        }
        else if (caracter == '-')
        {
            contador++;
            size_t posicionResta = funcion.find('-');
            // cout << " posicion resta: " << posicionResta << endl;
            termino = funcion.substr(0, posicionResta);
            funcionEnTerminos.push_back(termino);
            // cout << " termino " << contador << ": " << termino << endl;
            funcion = funcion.substr(posicionResta);
            // cout << "funcion restante: " << funcion << endl;
            i = 0;
        }
    }
    funcionEnTerminos.push_back(funcion);
}

void imprimirVector(vector<string> vector)
{
    for (auto it = vector.begin(); it != vector.end(); ++it)
    {
        cout << " vector: " << *it << endl;
    }
}

void reglaSimpson(double limiteA, double limiteB, double subintervalo, string funcionOriginal, vector<string> funcionEnTerminos)
{
    double resultado = 0;
    double resultadoSimpson = 0;
    double sumatoriaE = 0;
    double sumatoriaI = 0;
    double sumatoriaP = 0;
    string operacion = "";

    cout << " ------------------------------------------------------------------------------------------------------- " << endl;
    cout << "\t Xi \t|\t   X   \t|\t  E  \t\t|\t  I  \t\t|\t   P " << endl;
    cout << " ------------------------------------------------------------------------------------------------------- " << endl;

     
    int iteracion = 0;
    double valorActualX = limiteA;

    do {
        resultado = resolverPolinomio(funcionEnTerminos, valorActualX);
        if (iteracion == 0 || iteracion == 10)
        {
            cout << "\t  X" << iteracion << "\t|\t " << valorActualX << "\t|\t " << resultado << "\t\t|\t  -  \t\t|\t  -" << endl;
            sumatoriaE += resultado;
        }
        else if (iteracion % 2 == 0)
        {
            cout << "\t  X" << iteracion << "\t|\t " << valorActualX << "\t|\t  -  \t\t|\t  -  \t\t|\t " << resultado << endl;
            sumatoriaP += resultado;
        }
        else
        {
            cout << "\t  X" << iteracion << "\t|\t " << valorActualX << "\t|\t  -  \t\t|\t " << resultado << "\t|\t  -" << endl;
            sumatoriaI += resultado;
        }
        iteracion++;
        valorActualX += subintervalo;
    
    } while (iteracion <= N);

    cout << " ------------------------------------------------------------------------------------------------------- " << endl;
    cout << "  \t\t|  sumatorias\t|\t" << sumatoriaE << " \t|\t " << sumatoriaI << " \t|\t " << sumatoriaP << endl;
    cout << " ------------------------------------------------------------------------------------------------------- " << endl;

    resultadoSimpson = ((limiteB - limiteA) / 30) * (sumatoriaE + (4 * sumatoriaI) + (2 * sumatoriaP));
    cout << " ------------------------------------------------------------------------------------------------------- " << endl;
    cout << " resultado final: " << endl;
    cout << "[" << limiteA << " ; " << limiteB << "] | " << funcionOriginal << " ~= " << endl;
    cout << "[ (" << limiteB << " - " << limiteA << ") / ( 3 * 10 )] * [ " << sumatoriaE << " + ( 4 * " << sumatoriaI << " ) + ( 2 * " << sumatoriaP << " )] ~= " << resultadoSimpson << endl;
    cout << " ------------------------------------------------------------------------------------------------------- " << endl;
}

double resolverPolinomio(vector<string> vector, double valorX)
{
    double resultadoPolinomio = 0;
    for (string termino : vector)
    {
        // cout << " termino: " << termino << endl;
        double resultadoTermino = 0;

        string operacion = sumaResta(termino);
        if (operacion != "")
        {
            termino = termino.substr(1, (int)termino.length());
        }

        // cout << " operando en termino: [" << termino << "]" << endl;
        if (termino.find("x") != string::npos)
        {
            if (termino.find("^") != string::npos)
            {
                // cout << " resolviendo potencia..." << endl;
                resultadoTermino = resolverPotencia(termino, valorX);
            }
            else if (termino.find("/") != string::npos)
            {
                // cout << " resolviendo fraccion..." << endl;
                resultadoTermino = resolverFraccion(termino, valorX);
            }
            else
            {
                // cout << " resolviendo multiplicacion..." << endl;
                resultadoTermino = resolverMultiplicacion(termino, valorX);
            }
        }
        else
        {
            resultadoTermino = stoi(termino);
        }

        if (operacion == "+" || operacion == "")
        {
            // cout << "resultado del termino: " << resultadoTermino << endl;
            resultadoPolinomio += resultadoTermino;
            // cout << "resultado parcial del polinomio: " << resultadoPolinomio << endl;
        }
        else
        {
            // cout << "resultado del termino: " << resultadoTermino << endl;
            resultadoPolinomio -= resultadoTermino;
            // cout << "resultado parcial del polinomio: " << resultadoPolinomio << endl;
        }
    }
    // cout << "resultado total del polinomio: " << resultadoPolinomio << endl;
    return resultadoPolinomio;
}

string sumaResta(string termino)
{
    size_t suma = termino.find("+");
    size_t resta = termino.find("-");
    if (suma != string::npos)
    {
        // cout << " operacion: suma" << endl;
        return "+";
    }
    else if (resta != string::npos)
    {
        // cout << " operacion: resta" << endl;
        return "-";
    }
    else
    {
        // cout << " operacion: ninguna" << endl;
        return "";
    }
}

double resolverPotencia(string termino, double valorX)
{
    size_t indicePot = termino.find("^");
    // cout << "indice de la potencia: " << indicePot << endl;
    string antes = termino.substr(0, indicePot);
    // cout << " antes: " << antes << endl;
    termino = termino.substr(indicePot + 1);
    string despues = termino;
    // cout << " despues: " << despues << endl;

    antes = antes.substr(0, (antes.length() - 1));
    double numero = stoi(antes);
    // cout << " multiplicador: " << numero << endl;
    double exponente = stoi(despues);
    // cout << " exponente: " << exponente << endl;
    double resultado = pow(valorX, exponente) * numero;
    // cout << " resultado: " << resultado << endl;

    return resultado;
}

double resolverMultiplicacion(string termino, double valorX)
{
    size_t indiceMulti = termino.find("x");
    // cout << "indice de la x: " << indiceMulti << endl;
    string antes = termino.substr(0, indiceMulti);
    // cout << " antes: " << antes << endl;
    double multiplicador = stoi(antes);
    // cout << " multiplicador: " << multiplicador << endl;
    double resultado = valorX * multiplicador;
    // cout << " resultado: " << resultado << endl;

    return resultado;
}

double resolverFraccion(string termino, double valorX)
{
    int indiceX = termino.find("x");
    // cout << "indice de la x: " << indiceX << endl;
    string antes = termino.substr(0, indiceX);
    // cout << " antes: " << antes << endl;
    int indiceDiv = termino.find("/");
    // cout << "indice de la barra divisora: " << indiceDiv << endl;
    string dividendo_str = antes.substr(0, indiceDiv);
    string divisor_str = antes.substr(indiceDiv + 1);
    double dividendo = stoi(dividendo_str); // arriba
    // cout << " dividendo: " << dividendo << endl;
    double divisor = stoi(divisor_str); // abajo
    // cout << " divisor: " << divisor << endl;
    double resultado = (dividendo / divisor) * valorX;
    // cout << " resultado: " << resultado << endl;

    return resultado;
}
