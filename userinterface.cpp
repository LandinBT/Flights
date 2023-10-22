#include "userinterface.hpp"

void UserInterface::addCity() {
    City city;
    std::string str;
    int iInt;
    char op; //option

    do {
        cout<<"Nombre de la ciudad: ";
        std::getline(cin, str);
        city.setName(str);

        cout<<"Pais: ";
        std::getline(cin, str);
        city.setCountry(str);

        cout<<"No. de habitantes: ";
        cin>>iInt;
        cin.ignore();
        city.setPopulation(iInt);

        cities.addVertex(city);

        cout<<endl<<"Desea agregar otra ciudad? (s/n): ";
        cin>>op;
        cin.ignore();
        op=toupper(op);

        if(op!='S' and op!='N' and (cout<<"Opcion invalida!"<<endl, true)) {
            enterToContinue();
            }

        else cout<<endl<<endl<<endl;
        }
    while(op!='N');
    }

void UserInterface::addFlight() {
    City orig, dest;
    std::string str;
    int km;
    char op;

    do {
        cout<<"Ciudad de origen: ";
        std::getline(cin, str);
        orig.setName(str);

        cout<<"Ciudad de destino: ";
        std::getline(cin, str);
        dest.setName(str);

        cout<<"Distancia (km): ";
        cin>>km;
        cin.ignore();
        cities.addEdge(orig, dest, km);

        cout<<endl<<"Desea agregar otro vuelo? (s/n): ";
        cin>>op;
        cin.ignore();
        op=toupper(op);

        if(op!='S' and op!='N' and (cout<<"Opcion invalida!"<<endl, true)) {
            enterToContinue();
            }
        }
    while(op!='N');
    }

void UserInterface::deleteCity() {
    City city;
    std::string str;

    cout<<"Ciudad: ";
    std::getline(cin, str);
    }

void UserInterface::deleteFlight() {

    }

void UserInterface::showFlightsList() {
    cout<<"VUELOS"<<endl<<endl<<cities.toList();
    enterToContinue();
    }

void UserInterface::showFlightsMatrix() {
    cout<<"VUELOS"<<endl<<endl<<cities.toMatrix();
    enterToContinue();
    }


void UserInterface::save() {
    std::string str;

    cout<<"Nombre del archivo: ";
    std::getline(cin, str);

    //loading();

    cities.importToDisk(str);
    cout<<"Datos guardados correctamente"<<endl;
    enterToContinue();
    }

void UserInterface::load() {
    std::string str;

    cout<<"Nombre del archivo: ";
    std::getline(cin, str);

    //loading();

    cities.exportFromDisk(str);
    cout<<"Datos cargados correctamente"<<endl;
    enterToContinue();
    }

void UserInterface::enterToContinue() {
    cout<<"Presiona ENTER para continuar. . .";
    getchar();
    }

UserInterface::UserInterface() {
    short op; //option

    do {
        cout<<"A E R O L I N E A <-> G U A N A T O S"<<endl<<endl;
        cout<<"1. Agregar ciudad"<<endl;
        cout<<"2. Agregar vuelo"<<endl<<endl;
        cout<<"3. Borrar ciudad"<<endl;
        cout<<"4. Borrar vuelo"<<endl<<endl;
        cout<<"5. Mostrar vuelos (formato lista)"<<endl;
        cout<<"6. Mostrar vuelos (formato matriz)"<<endl<<endl;
        cout<<"7. Guardar"<<endl;
        cout<<"8. Cargar"<<endl<<endl;
        cout<<"0. Salir"<<endl<<endl;
        cout<<"Opcion: ";
        cin>>op;
        cin.ignore();

        if(op==0) cout<<endl<<endl;

        else system(CLEAR);

        switch(op) {
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
                save();
                break;

            case 8:
                load();
                break;

            case 0:
                cout<<"Gracias por usar el programa ;)"<<endl;
                exit(0);
                break;

            default:
                cout<<"Opcion invalida!"<<endl;
                enterToContinue();
                break;
            }

        system(CLEAR);
        }
    while(op!=0);
    }
