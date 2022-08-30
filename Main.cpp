#include <iostream>
#include <vector>
#include <set>
#include <map>

struct ElementoDeGrupo 
{
	std::vector<int> miniterminos;
	std::vector<int> valor;
};

auto getMiniterminosAndCount(const int miniTerminos, const int literalesCount)->std::pair<std::vector<int>, int>;
auto mergeElementoDeGrupo(std::map<int, std::vector<ElementoDeGrupo>> gruposNumerados, int literales, std::vector<ElementoDeGrupo> &noActualizada)->std::map<int, std::vector<ElementoDeGrupo>>;
void displayNuevaRespuesta(std::set<std::vector<int>> Respuesta);

void printMintermino(const std::vector<int> v);
void printEstado(const std::vector<int> v);
void printMinterminoIrr(const std::vector<int> v, const std::set<int> IrrSet); //Irr= irrelevantes
void printGrupos(const map<int, std::vector<ElementoDeGrupo>> allGrupos, const std::set<int>IrrSet);
void printNoActualizada(std::vector<ElementoDeGrupo> noActualizada);

int main() {
#ifdef Prueba
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	// Cabecera
	cout << "\n Tecnica de Agrupacion Quine McCluskey\n";

	// SetUp
	cout << "\n--------------------------------------------------\n";

	int literalesCount;
	cout << "Digite el numero de literales(mayores a cero): ";
	cin >> literalesCount;

	int miniTerminosCount;
	cout << "Numero de Miniterminos: ";
	cin >> minTerminosCount;
	set<int> miniTerminosSet;
	cout << "Digite los miniterminos dejando espacio entre ellos(ej. 1 2 3): " << endl;
	for (int i = 0; i < miniTerminosCount; ++i)
	{
		int minitermino;
		cin >> minitermino;
		miniTerminosSet.insert(minitermino);
	}

	int IrrTermsCount;
	cout << "Numero de terminos irrelevantes: ";
	cin >> IrrTermsCount;
	set<int> IrrTermsCount;
	cout << "Digite los terminos irrelevantes dejando espacio entre ellos(ej. 1 2 3): " << endl;
	for (int i = 0; i < IrrTermsCount; ++i)
	{
		int IrrTerm;
		cin >> IrrTerm;
		IrrTermsSet.insert(IrrTerm);
	}

	cout << "\n--------------------------------------------------\n";

	// Agrupando 
	map<int, vector<ElementoDeGrupo>> gruposNumerados;

	// Agregando los miniterminos a los grupos Numerados
	set<int> totalTerminos;
	totalTerminos.insert(miniTerminosSet.begin(), miniTerminosSet.end());
	totalTerminos.insert(IrrTermsSet.begin(), IrrTermsSet.end());
	for (auto terminos : totalTerminos)
	{
		pair<vector<int>, int> result = getMiniterminosAndCount(termino, literalesCount);

		// Crear un Elemento de Grupo 
		ElementoDeGrupo grupoEle;
		grupoEle.miniterminos.push_back(termino);
		grupoEle.valor = result.first;

		// Agrega el elemento al grupo correspondiente
		gruposNumerados[result.second].push_back(grupoEle);

		// Imprime el minitermino y su valor 
		cout << term << ": ";
		printMinitermino(result.first);
		cout << endl;
	}

}