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
void printGrupos(const std::map<int, std::vector<ElementoDeGrupo>> allGrupos, const std::set<int>IrrSet);
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
	for (int i = 0; i < miniterminosCount; ++i)
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
    // Ahora imprime todos los grupos 
	cout << "\n--------------------------------------------------\n";
	cout << "Miniterminos agrupados y los irrelevantes : \n" << endl;
	printGrupos(gruposNumerados, IrrTermsSet);

	// Merging the Groups and printing them
	// and not updated groups are those which were not considred during merge
	vector<ElementoDeGrupo> NoActualizada;
	while (true) {
		map<int, vector<ElementoDeGrupo>> newGruposNumerados = mergeElementoDeGrupo(gruposNumerados, literalesCount, noActualizada);

		if (newGruposNumerados.size() == 0 ) break;
		gruposNumerados = newGruposNumerados;

		// Imprime todos los grupos 
		cout << "\n--------------------------------------------------\n";
		cout << "Agrupar los miniterminos y los irrelevantes: \n" << endl;
		printGrupos(gruposNumerados, IrrTermsSet);
	}

	// Imprime los terminos faltantes despues de merging 
	cout << "\n--------------------------------------------------\n";
	cout << "Terminos olvidados en la merging " << endl;
	printNoActualizada(noActualizada);

	// Step to get the minterm and the table of them

	// going through the table and taking the minterms which appear only once in the table
	// and adding it to the answer
	map<int, int> countEnTabla;
	set<vector<int>> seenMiniterminos; // Used for identifying the seen minterms

	for (auto& group : gruposNumerados) {
		for (auto& ElementoDeGrupo : grupo.second) {

			// Revisa si el minitermino se puede ver o no 
			if (seenMiniterminos.count(ElementoDeGrupo.value)) continue;
			seenMiniterminos.insert(ElementoDeGrupo.value);

			// Agrega miniterminos a la tabla 
			for (auto& minitermino : ElementoDeGrupo.minterminos) {
				if (!IrrTermsSet.count(minitermino)) {
					countEnTabla[minitermino]++;
				}
			}
		}
	}

	// Adding other prime implicants which were lost during merging
	for (auto& ElementoDeGrupo : noActualizada) {
		if (seenMiniterminos.count(ElementoDeGrupo.value)) continue;
		seenMiniterminos.insert(ElementoDeGrupo.value);
		// printState(ElementoDeGrupo.value);
		// cout << endl;
		for (auto& mintermino : ElementoDeGrupo.minterminos) {
			if (!IrrTermsSet.count(mintermino)) {
				countEnTabla[mintermino]++;
			}
		}
	}

	// Ahora se saca una nueva respuesta 
	set<vector<int>> respuesta;

	// revisa los terminos individuales para estar seguros de que chequea todos los terminos 
	set<int> terminosTomados;
	for (auto& cell : countEnTabla) {
		if (cell.second == 1)
		{
			for (auto& gp : gruposNumerados) {
				for (auto& ele : gp.second) {
					int count = 0;
					for (auto& num : ele.minterms) {
						if (cell.first == num)count++;
					}
					if (count != 0) {
						respuesta.insert(ele.valor);
						for (auto& num : ele.miniterminos) {
							terminosTomados.insert(num);
						}
					}
				}
			}
		}
	}

	// Imprime la tabla
	cout << "\n--------------------------------------------------\n";
	cout << "Terms with the occurnce of them: " << endl;
	for (auto& i : countEnTabla) {
		cout << i.first << ": " << i.second << endl;
	}

	// Finding the elements left in countable which are not included
	// The logic suggest that if the term is in the count table then it is in any of the elements

	for (auto& iterator : countEnTabla) {
		if (!terminosTomados.count(iterator.first))
		{
			bool flag = false;
			// cout << iterator.first << endl;
			for (auto& gp : gruposNumerados) {
				for (auto& ele : gp.second) {
					for (auto& j : ele.miniterminos) {
						if (iterator.first == j) {
							respuesta.insert(ele.valor);
							flag = true;
							break;
						}
					}
					if (flag) break;
				}
				if (flag) break;
			}

			// Revisa si es la acualizada
			for (auto& j : noActualizada) {
				for (auto& k : j.miniterminos) {
					if (iterator.first == k) {
						respuesta.insert(j.valor);
						flag = true;
						break;
					}
				}
				if (flag) break;
			}
		}
	}

	// This is for the remaining onesfor which is not included
	for (auto& minitermino : miniTerminosSet) {
		if (!countEnTabla.count(miniterminos)) {
			respuesta.insert(getMiniterminosAndCount(minitermino, literalesCount).first);
		}
	}

	// muestra la respuesta
	cout << "\n--------------------------------------------------\n";
	cout << "La ecuacion minimizada: ";
	displayRespuestaFormateada(respuesta);

	return 0;
}

pair<vector<int>, int> getMiniterminosAndCount(const int minitermino, const int literalesCount) {
	vector<int> miniterminoVector;
	int unosCount = 0;

	for (int i = 0; i < literalesCount; ++i)
	{
		if (minitermino & 1 << (literalesCount - i - 1)) {
			miniterminoVector.push_back(1);
			unosCount++;
		}
		else
		{
			miniterminoVector.push_back(0);
		}
	}

	pair<vector<int>, int> miniterminoAndCount;
	miniterminoAndCount.first = miniterminoVector;
	miniterminoAndCount.second = unosCount;

	return miniterminoAndCount;
}

// merging function
map<int, vector<ElementoDeGrupo>> mergeElementoDeGrupo(map<int, vector<ElementoDeGrupo>> gruposNumerados, int literales, vector<ElementoDeGrupo> &noActualizada) {
	// Merged groups will be added here
	map<int, vector<ElementoDeGrupo>> newGruposNumerados;
	int updateCount = 0;

	set<vector<int>> termsUsed;

	for (auto& grupo : gruposNumerados) {
		if (gruposNumerados.count(grupo.first + 1))
		{
			int grupoCompletoNoActualizado = 0;
			for (auto& ElementoDeGrupo : grupo.second) {
				// Checking if next group is present or not
				// Comparing the elements with the next group elements
				for (auto& nextElementoDeGrupo : gruposNumerados[grupo.first + 1]) {
					int diffIndex = -1;
					int diffCount = 0;

					for (int i = 0; i < literales; ++i)
					{
						if (ElementoDeGrupo.valor[i] != nextElementoDeGrupo.valor[i]) {
							diffIndex = i;
							diffCount++;
						}
					}

					if (diffCount == 1) {
						updateCount++;
						grupoCompletoNoActualizado++;

						ElementoDeGrupo newElementoDeGrupo;

						newElementoDeGrupo.valor = ElementoDeGrupo.valor;
						newElementoDeGrupo.valor[diffIndex] = -1;

						// Adding new minters

						newElementoDeGrupo.miniterminos = ElementoDeGrupo.miniterminos;
						for (auto& m : nextElementoDeGrupo.miniterminos) {
							newElementoDeGrupo.miniterminos.push_back(m);
						}

						terminosUsados.insert(ElementoDeGrupo.miniterminos);
						terminosUsados.insert(nextElementoDeGrupo.miniterminos);

						// Adding new numbered group
						newGruposNumerados[grupo.first].push_back(newElementoDeGrupo);
					}
				}
			}
		}
	}

	if (updateCount == 0) return {};

	for (auto& grupo : gruposNumerados) {
		for (auto& ElementoDeGrupo : grupo.second) {
			if (!terminosUsados.count(ElementoDeGrupo.miniterminos))
			{
				noActualizada.push_back(ElementoDeGrupo);
			}
		}
	}

	return newGruposNumerados;
}

void displayRespuestaFormateada(set<vector<int>> respuesta) {
	for (auto& i : respuesta) {
		char letra = 'A';
		for (auto& j : i) {
			if (j != -1) {
				if (j == 1)
				{
					cout << letra;
				} else {
					cout << "~" << letra;
				}
			}
			letra++;
		}
		cout << " + ";
	}
	cout << "\b\b" << "  " << endl;
}

// Imprime funciones
void printMiniterminos(const vector<int> v) {
	for (int i = 0; i < v.size(); ++i)	{
		cout << v[i] << " ";
	}
}

void printEstado(const vector<int> v) {
	for (int i = 0; i < v.size(); ++i)	{
		if (v[i] == -1)
		{
			cout << "_" << " ";
		} else {
			cout << v[i] << " ";
		}
	}
}

void printMiniterminosConIrr(const vector<int> v, const set<int> IrrSet) {
	for (int i = 0; i < v.size(); ++i)	{
		if (IrrSet.count(v[i])) cout << v[i] << "* ";
		else cout << v[i] << "  ";
	}
}

// For printing the Group
void printGrupos(const map<int, vector<ElementoDeGrupo>> allGrupos, const set<int>IrrSet) {
	for (auto& grupo : allGrupos) {
		cout << "Grupo " << grupo.first << endl;
		for (auto& ElementoDeGrupo : grupo.second) {
			printMiniterminosConIrr(ElementoDeGrupo.miniterminos, IrrSet);
			cout << ": ";
			printEstado(ElementoDeGrupo.valor);
			cout << endl;
		}
	}
}

void printNoActualizada(vector<ElementoDeGrupo> noActualizada) {
	cout << endl;
	for (auto& ElementoDeGrupo : noActualizada) {
		printMiniterminos(ElementoDeGrupo.miniterminos);
		cout << ": ";
		printEstado(ElementoDeGrupo.valor);
		cout << endl;
	}
	cout << endl;
}
