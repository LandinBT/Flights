#include "userinterface.hpp"

void UserInterface::addCity() {
  City city;
  std::string str;
  unsigned long long iUnsLong;
  char op;  // option

  do {
    cout << "Nombre de la ciudad: ";
    std::getline(cin, str);
    city.setName(str);

    cout << "Pais: ";
    std::getline(cin, str);
    city.setCountry(str);

    cout << "No. de habitantes: ";
    cin >> iUnsLong;
    city.setPopulation(iUnsLong);
    cin.ignore();

    try {
      citiesPtr->addVertex(city);
    } catch (const Graph<City>::Exception& ex) {
      cout << endl << "Algo salio mal: " << ex.what() << endl;
    }

    cout << endl << "Desea agregar otra ciudad? (s/n): ";
    cin >> op;
    cin.ignore();
    op = toupper(op);

    if (op != 'S' and op != 'N' and
        (cout << "Opcion invalida!" << endl, true)) {
      enterToContinue();
    }

    else
      cout << endl << endl << endl;
  } while (op != 'N');
}

void UserInterface::addFlight() {
  City orig, dest;
  std::string str;
  int km;
  char op;

  do {
    cout << "Ciudad de origen: ";
    std::getline(cin, str);
    orig.setName(str);

    cout << "Ciudad de destino: ";
    std::getline(cin, str);
    dest.setName(str);

    cout << "Distancia (km): ";
    cin >> km;
    cin.ignore();

    try {
      citiesPtr->addEdge(orig, dest, km);
    } catch (const Graph<City>::Exception& ex) {
      cout << endl << "Algo salio mal: " << ex.what() << endl;
    }

    cout << endl << "Desea agregar otro vuelo? (s/n): ";
    cin >> op;
    cin.ignore();
    op = toupper(op);

    if (op != 'S' and op != 'N' and
        (cout << "Opcion invalida!" << endl, true)) {
      enterToContinue();
    }
  } while (op != 'N');
}

void UserInterface::deleteCity() {
  City city;
  std::string str;
  char op;  // option

  do {
    cout << "Nombre de la ciudad: ";
    std::getline(cin, str);
    city.setName(str);

    try {
      citiesPtr->deleteVertex(city);
    } catch (const Graph<City>::Exception& ex) {
      cout << endl << "Algo salio mal: " << ex.what() << endl;
    }

    cout << endl << "Desea eliminar otra ciudad? (s/n): ";
    cin >> op;
    cin.ignore();
    op = toupper(op);

    if (op != 'S' and op != 'N' and
        (cout << "Opcion invalida!" << endl, true)) {
      enterToContinue();
    }

    else
      cout << endl << endl << endl;
  } while (op != 'N');
}

void UserInterface::deleteFlight() {
  City orig, dest;
  std::string str;
  char op;

  do {
    cout << "Ciudad de origen: ";
    std::getline(cin, str);
    orig.setName(str);

    cout << "Ciudad de destino: ";
    std::getline(cin, str);
    dest.setName(str);

    try {
      citiesPtr->deleteEdge(orig, dest);
    } catch (const Graph<City>::Exception& ex) {
      cout << endl << "Algo salio mal: " << ex.what() << endl;
    }

    cout << endl << "Desea eliminar otro vuelo? (s/n): ";
    cin >> op;
    cin.ignore();
    op = toupper(op);

    if (op != 'S' and op != 'N' and
        (cout << "Opcion invalida!" << endl, true)) {
      enterToContinue();
    }
  } while (op != 'N');
}

void UserInterface::showFlightsList() {
  cout << "VUELOS" << endl << endl << citiesPtr->toList() << endl;
  enterToContinue();
}

void UserInterface::showFlightsMatrix() {
  cout << "VUELOS" << endl << endl << citiesPtr->toMatrix() << endl;
  enterToContinue();
}

void UserInterface::deleteAll() {
  char op;

  cout << "Desea eliminar todas las ciudades y todos los vuelos? (s/n): ";
  cin >> op;
  cin.ignore();
  op = toupper(op);

  if (op == 'S') {
    citiesPtr->deleteAll();
    cout << endl << "Datos eliminados correctamente!" << endl;
  } else if (op != 'S' and op != 'N')
    cout << endl << "Opcion invalida!" << endl;

  enterToContinue();
}

void UserInterface::save() {
  std::string str;

  cout << "Nombre del archivo: ";
  std::getline(cin, str);

  // loading();

  try {
    citiesPtr->exportFromDisk(str);
    cout << endl << "Datos guardados correctamente" << endl;
  } catch (const std::ios_base::failure& ex) {
    cout << endl << ex.what() << endl;
  }

  enterToContinue();
}

void UserInterface::load() {
  std::string str;

  cout << "Nombre del archivo: ";
  std::getline(cin, str);

  // loading();

  try {
    citiesPtr->importToDisk(str);
    cout << endl << "Datos cargados correctamente" << endl;
  } catch (const std::ios_base::failure& ex) {
    cout << endl << ex.what() << endl;
  }

  enterToContinue();
}

void UserInterface::enterToContinue() {
  cout << "Presiona ENTER para continuar. . .";
  getchar();
}

UserInterface::UserInterface() {
  citiesPtr = new Graph<City>;
  short op;  // option

  do {
    cout << "A E R O L I N E A <-> G U A N A T O S" << endl << endl;
    cout << "1. Agregar ciudad" << endl;
    cout << "2. Agregar vuelo" << endl << endl;
    cout << "3. Borrar ciudad" << endl;
    cout << "4. Borrar vuelo" << endl << endl;
    cout << "5. Mostrar vuelos (formato lista)" << endl;
    cout << "6. Mostrar vuelos (formato matriz)" << endl << endl;
    cout << "7. Borrar todo" << endl << endl;
    cout << "8. Guardar" << endl;
    cout << "9. Cargar" << endl << endl;
    cout << "0. Salir" << endl << endl;
    cout << "Opcion: ";
    cin >> op;
    cin.ignore();

    if (op == 0)
      cout << endl << endl;

    else
      system(CLEAR);

    switch (op) {
      case 1:
        addCity();
        break;

      case 2:
        addFlight();
        break;

      case 3:
        deleteCity();
        break;

      case 4:
        deleteFlight();
        break;

      case 5:
        showFlightsList();
        break;

      case 6:
        showFlightsMatrix();
        break;

      case 7:
        deleteAll();
        break;

      case 8:
        save();
        break;

      case 9:
        load();
        break;

      case 0:
        cout << "Gracias por usar el programa ;)" << endl;
        exit(0);
        break;

      default:
        cout << "Opcion invalida!" << endl;
        enterToContinue();
        break;
    }

    system(CLEAR);
  } while (op != 0);
}

UserInterface::~UserInterface() {
  if (citiesPtr != nullptr) {
    delete citiesPtr;
    citiesPtr = nullptr;
  }
}
