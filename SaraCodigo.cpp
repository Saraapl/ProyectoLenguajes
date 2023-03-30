#include <iostream>
#include <string>
using namespace std;

// Clase Abstracta
class Articulo {
public:
  int ID;
  string nombre;
  double precio;
  Articulo(int ID, string n, double p) {
    this->ID = ID;
    this->nombre = n;
    this->precio = p;
  }
  // Metodo virtual puro
  virtual string getTipo() = 0;
};

class ArticuloTecnologia : public Articulo {
public:
  string marca;
  ArticuloTecnologia(int ID, string n, double p, string m)
      : Articulo(ID, n, p) {
    this->marca = m;
  }
  string getTipo() { return " TECNOLOGIA "; }
};

class ArticuloExtranjero : public Articulo {
public:
  double impuesto;
  ArticuloExtranjero(int ID, string n, double p, double i)
      : Articulo(ID, n, p), impuesto(i) {}
  string getTipo() { return " EXTRANJERO"; }
};

class ArticuloDeporte : public Articulo {
public:
  string deporte;
  ArticuloDeporte(int ID, string n, double p, string d) : Articulo(ID, n, p) {
    this->deporte = d;
  }
  string getTipo() { return " DEPORTE"; }
};

class Nodo {
public:
  Articulo *valor;
  Nodo *siguiente = NULL;
  Nodo(Articulo *v) { this->valor = v; }
};

class Inventario {
public:
  Nodo *head = NULL;

public:
  Nodo *agregarNodo(Articulo *articulo) {
    Nodo *nuevo = new Nodo(articulo);
    if (this->head == NULL) {
      this->head = nuevo;
      return nuevo;
    }
    Nodo *actual = this->head;
    while (actual->siguiente != NULL) {
      actual = actual->siguiente;
    }
    actual->siguiente = nuevo;
    return nuevo;
  }

  bool eliminarNodo(string dato, string tipo) {
    if (head == NULL) {
      return false;
    }
    if (head->valor->nombre == dato) {
      head = head->siguiente;
      return true;
    }
    Nodo *prev = head;
    Nodo *actual = prev->siguiente;
    while (actual != NULL) {
      if (actual->valor->nombre == dato && actual->valor->getTipo() == tipo) {
        prev->siguiente = actual->siguiente;
        return true;
      }
      prev = actual;
      actual = actual->siguiente;
    }
    return false;
  }

  void cambiarAtributos(int id, int opt) {
    Nodo *actual = head;
    bool encontrado = false;

    while (actual != NULL) {
      if (actual->valor->ID == id) {
        encontrado = true;

        if (opt == 1) {
          string nombre;
          cout << "Ingrese el nuevo nombre del articulo: ";
          cin >> nombre;
          actual->valor->nombre = nombre;
          cout << "Modificado correctamente" << endl;
        } else if (opt == 2) {
          float precio;
          cout << "Ingrese el nuevo precio del articulo: ";
          cin >> precio;
          actual->valor->precio = precio;
          cout << "Modificado correctamente" << endl;
        } else {
          cout << "Opcion invalida" << endl;
        }
      }

      actual = actual->siguiente;
    }

    if (!encontrado)
      cout << "El articulo no fue encontrado" << endl;
  }

  void imprimirTodo() {
    Nodo *actual = this->head;
    while (actual != nullptr) {
      cout << "Articulo de " << actual->valor->getTipo() << ":";
      cout << " ID: " << actual->valor->ID
           << ", Nombre: " << actual->valor->nombre
           << ", Precio: " << actual->valor->precio << endl;
      actual = actual->siguiente;
    }
  }
  void imprimirTipo(string tipo) {
    Nodo *actual = this->head;
    while (actual != nullptr) {
      if (actual->valor->getTipo() == tipo) {
        cout << "ID: " << actual->valor->ID
             << ", Nombre: " << actual->valor->nombre
             << ", Precio: " << actual->valor->precio << endl;
      }
      actual = actual->siguiente;
    }
  }
};

class CarritoCompra : public Inventario {
  public:
  void comprobarDescuento(string nombreComprado){
    Nodo *actual = this->head;
    Nodo *prev = NULL;
    while (actual != nullptr) {
      if (prev != NULL && prev->valor->nombre == actual->valor->nombre && prev->valor->nombre == nombreComprado) {
        cout << "Obtendras un descuento del 10% en la compra del articulo: " << actual->valor->nombre << endl;
        cout << "Precio original: " << actual->valor->precio << endl;
        cout << "Precio con descuento: " << actual->valor->precio * 0.9 << endl;
      }
      prev = actual;
      actual = actual->siguiente;
    }
  }
};

class Coordinador {
private:
  Inventario &inventario;

public:
  Coordinador(Inventario &inventario) : inventario(inventario) {}
  // inicializar los atributos de la clae, member inicialization

  void menu_coordinador() {
    int opcionCoordinador;
    int opcionCoordinador2;
    cout << "Bienvenido coordinador, presione 1 para agregar artículos" << endl;
    cout << " 2 para modificar artículos" << endl;
    cout << "y 3 para eliminar artículos" << endl;
    cin >> opcionCoordinador;

    if (opcionCoordinador == 1) {
      cout << "Presione 1  para agregar un articulo de tecnologia" << endl;
      cout << "2 para agregar un articulo de deporte y 3 para agregar un "
              "articulo extranjero"
           << endl;
      cin >> opcionCoordinador2;
      if (opcionCoordinador2 == 1) {
        cout << "Agregue el nuevo artículo" << endl;
        cout << "Agregue el ID del articulo" << endl;
        int ID;
        cin >> ID;
        cout << "Agregue el nombre del articulo" << endl;
        string nombre;
        cin >> nombre;
        cout << "Agregue el precio del articulo" << endl;
        float precio;
        cin >> precio;
        string marca;
        cout << "Agregue la marca del articulo" << endl;
        cin >> marca;
        ArticuloTecnologia *articuloTec =
            new ArticuloTecnologia(ID, nombre, precio, marca);
        inventario.agregarNodo(articuloTec);
        cout << "Su artículo ha sido creado con éxito!" << endl;
        cout << "Los articulos de tecnologia creados son: " << endl;
        inventario.imprimirTipo("TECNOLOGIA");
      } else if (opcionCoordinador2 == 2) {
        cout << "Agegue el nuevo artículo" << endl;
        cout << "Aguegue el ID del articulo" << endl;
        int ID;
        cin >> ID;
        cout << "Agregue el nombre del articulo" << endl;
        string nombre;
        cin >> nombre;
        cout << "Agregue el precio del articulo" << endl;
        float precio;
        cin >> precio;
        string deporte;
        cout << "Diga de que deporte es el articulo" << endl;
        cin >> deporte;
        ArticuloDeporte *articuloDep =
            new ArticuloDeporte(ID, nombre, precio, deporte);
        inventario.agregarNodo(articuloDep);
        cout << "Su artículo ha sido creado con éxito!" << endl;
        cout << "Los articulos agregados a la lista son: " << endl;
        inventario.imprimirTipo("DEPORTE");
      } else {
        if (opcionCoordinador2 == 3) {
          cout << "Agregue el nuevo artículo" << endl;
          cout << "Agregue el ID del articulo" << endl;
          int ID;
          cin >> ID;
          cout << "Agregue el nombre del articulo" << endl;
          string nombre;
          cin >> nombre;
          cout << "Agregue el precio del articulo" << endl;
          float precio;
          cin >> precio;
          double impuesto;
          cout << "Agregue el impuesto del articulo" << endl;
          cin >> impuesto;
          ArticuloExtranjero *articuloExt =
              new ArticuloExtranjero(ID, nombre, precio, impuesto);
          inventario.agregarNodo(articuloExt);
          cout << "Su artículo ha sido creado con éxito!" << endl;
        }
      }
    }
    if (opcionCoordinador == 2) {
      cout << "Ingrese 1 para modificar articulos de tecnología" << endl;
      cout << ", Ingrese 2 para modificar articulos de deporte y 3 para "
              "modificar articulos extranjeros"
           << endl;
      int opt;
      cin >> opt;
      if (opt == 1) {
        cout << "Está modificando la lista de tecnología\n" << endl;
        inventario.imprimirTipo("TECNOLOGIA");
        cout << "Ingrese el ID del articulo que desea modificar: ";
        int id;
        cin >> id;
        cout << "Ingrese 1 para cambiar el nombre o ingrese 2 para cambiar "
                "el precio: ";
        int opt;
        cin >> opt;
        inventario.cambiarAtributos(id, opt);
      }
      if (opt == 2) {
        cout << "Está modificando la lista deportiva\n" << endl;
        inventario.imprimirTipo("DEPORTE");
        cout << "Ingrese el ID del articulo que desea modificar: ";
        int id;
        cin >> id;
        cout << "Ingrese 1 para cambiar el nombre o ingrese 2 para cambiar "
                "el precio: ";
        int opt;
        cin >> opt;

        inventario.cambiarAtributos(id, opt);
      }
      if (opt == 3) {
        cout << "Está modificando la lista extranjero\n" << endl;
        inventario.imprimirTipo("EXTRANJERO");
        cout << "Ingrese el ID del articulo que desea modificar: ";
        int id;
        cin >> id;
        cout << "Ingrese 1 para cambiar el nombre o ingrese 2 para cambiar "
                "el precio: ";
        int opt;
        cin >> opt;
        inventario.cambiarAtributos(id, opt);
      }
    }
    if (opcionCoordinador == 3) {
      cout << "Ingrese 1 para eliminar un articulo de tecnologia, 2 " << endl;
      cout << "Para eliminar un arituculo de deporte y 3 para eliminar "
              "articulo extranjero"
           << endl;
      int opcionCoordinador3;
      cin >> opcionCoordinador3;
      if (opcionCoordinador3 == 1) {
        cout << "Ingrese el nombre del articulo que desea eliminar" << endl;
        string dato;
        cin >> dato;
        inventario.eliminarNodo(dato, "TECNOLOGIA");
        cout << "El articulo ha sido eliminado con exito, los articulos "
                "disponibles son: "
             << endl;
        inventario.imprimirTipo("TECNOLOGIA");
      } else if (opcionCoordinador3 == 2) {
        cout << "Ingrese el nombre del articulo que desea eliminar" << endl;
        string dato;
        cin >> dato;
        inventario.eliminarNodo(dato, "DEPORTE");
        cout << "El articulo ha sido eliminado con exito, los articulos "
                "disponibles son: "
             << endl;
        inventario.imprimirTipo("DEPORTE");
      } else {
        cout << "Ingrese el nombre del articulo que desea eliminar" << endl;
        string dato;
        cin >> dato;
        inventario.eliminarNodo(dato, "EXTRANJERO");
        cout << "El articulo ha sido eliminado con exito, los articulos "
                "disponibles son: "
             << endl;
        inventario.imprimirTipo("EXTRANJERO");
      }
    }
  }
};

class Usuario {
private:
  Inventario &inventario;
  CarritoCompra &inventarioCompra;

public:
  Usuario(Inventario &inventarioGeneral, CarritoCompra &inventarioCompra)
      : inventario(inventarioGeneral), inventarioCompra(inventarioCompra) {}
  void menu_usuario() {
    int opcionUsuario;
    cout << "Bienvenido usuario, presione 1 para ver articulos y 2 para "
            "comprar"
         << endl;
    cin >> opcionUsuario;
    if (opcionUsuario == 1) {
      cout << "Presione 1 para ver articulos de tecnologia, 2 para " << endl;
      cout << " ver articulos de deporte y 3 para ver articulo extranjero"
           << endl;
      int opcionUsuarioArt;
      cin >> opcionUsuarioArt;
      if (opcionUsuarioArt == 1) {
        cout << "Los articulos de tecnologia que tenemos disponibles son los "
                "siguientes: "
             << endl;
        inventario.imprimirTipo("TECNOLOGIA");
      } else if (opcionUsuarioArt == 2) {
        cout << "Los articulos de deporte que tenemos disponibles son los "
                "siguientes: "
             << endl;
        inventario.imprimirTipo("DEPORTE");
      } else {
        cout << "Los articulos de deporte que tenemos disponibles son los "
                "siguientes: "
             << endl;
        inventario.imprimirTipo("EXTRANJERO");
      }
    } else if (opcionUsuario == 2) {
      cout << "Presione 1 para comprar un articulo de tecnologia,"
              "comprar "
           << endl;
      cout << "2 para comprar articulos de deporte y 3 para comprar articulos "
              "extranjeros"
           << endl;
      int opcionUsuariocompra;
      cin >> opcionUsuariocompra;
      if (opcionUsuariocompra == 1) {
        cout << "Ingrese el nombre del articulo que desea comprar" << endl;
        string nombreArticuloComprado;
        cin >> nombreArticuloComprado;
        cout << "Ingrese el ID del articulo que desea comprar" << endl;
        int IDart;
        cin >> IDart;
        cout << "Ingrese el precio del articulo que desea comprar" << endl;
        float precioArt;
        cin >> precioArt;
        string marca;
        cout << "Ingrese la marca del articulo que desea comprar" << endl;
        cin >> marca;
        ArticuloTecnologia *articulo = new ArticuloTecnologia(
            IDart, nombreArticuloComprado, precioArt, marca);
        // inventarioCompra.eliminarNodo(nombreArticuloComprado, "TECNOLOGIA");
        Nodo *nodoInsertado = inventarioCompra.agregarNodo(articulo);
        cout << "Su lista de compra actual es :" << endl;
        inventarioCompra.imprimirTodo();
        cout << "Si desea pagar, escriba 1, si no, escriba 2" << endl;
        int opcionComprar;
        cin >> opcionComprar;
        if (opcionComprar == 1) {
          cout << "Para pagar, ingrese los siguientes datos: " << endl;
          cout << "Ingrese su nombre:" << endl;
          string nombre;
          cin >> nombre;
          cout << "Ingrese la dirección de la entrega: " << endl;
          string direccion;
          cin >> direccion;
          cout << "Ingrese su numero de telefono: " << endl;
          string numero;
          cin >> numero;
          inventarioCompra.comprobarDescuento(articulo->nombre);
          inventarioCompra.eliminarNodo(articulo->nombre, "TECNOLOGIA");
          cout << "Se ha realizado la compra con éxito, llegará a su dirección "
                  "en "
               << endl;
          cout << "aproximadamente 1 semana, con pago contraentrega. Su nueva "
                  "lista "
               << endl;
          cout << "de compra es: " << endl;
          inventarioCompra.imprimirTodo();
        } else {
          return;
        }
      } else if (opcionUsuariocompra == 2) {
        cout << "Ingrese el nombre del articulo que desea comprar" << endl;
        string nombreArticuloComprado;
        cin >> nombreArticuloComprado;
        cout << "Ingrese el ID del articulo que desea comprar" << endl;
        int IDart;
        cin >> IDart;
        cout << "Ingrese el precio del articulo que desea comprar" << endl;
        float precioArt;
        cin >> precioArt;
        string deporte;
        cout << "Ingrese el deporte del articulo que desea comprar" << endl;
        cin >> deporte;
        ArticuloDeporte *articulo = new ArticuloDeporte(
            IDart, nombreArticuloComprado, precioArt, deporte);
        Nodo *nodoInsertado = inventarioCompra.agregarNodo(articulo);
        cout << "Su lista de compra actual es :" << endl;
        inventarioCompra.imprimirTodo();
        cout << "Si desea pagar, escriba 1, si no, escriba 2" << endl;
        int usuarioPagar;
        cin >> usuarioPagar;
        if (usuarioPagar == 1) {
          cout << "Para pagar, ingrese los siguientes datos: " << endl;
          cout << "Ingrese su nombre:" << endl;
          string nombre;
          cin >> nombre;
          cout << "Ingrese la dirección de la entrega: " << endl;
          string direccion;
          cin >> direccion;
          cout << "Ingrese su numero de telefono: " << endl;
          string numero;
          cin >> numero;
          inventarioCompra.comprobarDescuento(articulo->nombre);
          inventarioCompra.eliminarNodo(articulo->nombre, "DEPORTE");
          cout << "Se ha realizado la compra con éxito, llegará a su dirección "
                  "en "
               << endl;
          cout << "aproximadamente 1 semana, con pago contraentrega. Su nueva "
                  "lista "
               << endl;
          cout << "de compra es: " << endl;
          inventarioCompra.imprimirTodo();
        } else {
          return;
        }
      } else if (opcionUsuariocompra == 3) {
        cout << "Ingrese el nombre del articulo que desea comprar" << endl;
        string nombreArticuloComprado;
        cin >> nombreArticuloComprado;
        cout << "Ingrese el ID del articulo que desea comprar" << endl;
        int IDart;
        cin >> IDart;
        cout << "Ingrese el precio del articulo que desea comprar" << endl;
        float precioArt;
        cin >> precioArt;
        double impuesto;
        cout << "Ingrese el impuesto del articulo que desea comprar" << endl;
        cin >> impuesto;
        ArticuloExtranjero *articulo = new ArticuloExtranjero(
            IDart, nombreArticuloComprado, precioArt, impuesto);
        // inventarioCompra.eliminarNodo(nombreArticuloComprado, "EXTRANJERO");
        Nodo *nodoInsertado = inventarioCompra.agregarNodo(articulo);
        cout << "Su lista de compra actual es :" << endl;
        inventarioCompra.imprimirTodo();
        cout << "Si desea pagar, escriba 1, si no, escriba 2" << endl;
        int usuarioPagar;
        cin >> usuarioPagar;
        if (usuarioPagar == 1) {
          cout << "Para pagar, ingrese los siguientes datos: " << endl;
          cout << "Ingrese su nombre:" << endl;
          string nombre;
          cin >> nombre;
          cout << "Ingrese la dirección de la entrega: " << endl;
          string direccion;
          cin >> direccion;
          cout << "Ingrese su numero de telefono: " << endl;
          string numero;
          cin >> numero;
          inventarioCompra.comprobarDescuento(articulo->nombre);
          inventarioCompra.eliminarNodo(articulo->nombre, "EXTRANJERO");
          cout << "Por comprar un articulo extranjero, se le pondrá un "
                  "impuesto del "
               << articulo->impuesto << " % del precio " << endl;
          cout << "Se ha realizado la compra con éxito, llegará a su dirección "
                  "en "
               << endl;
          cout << "aproximadamente 1 semana, con pago contraentrega. Su nueva "
                  "lista "
               << endl;
          cout << "de compra es: " << endl;
          inventarioCompra.imprimirTodo();
        } else {
          return;
        }
      }
    }
  }
};

class Controlador {
private:
  Inventario inventario;
  CarritoCompra inventarioCompra;
  Coordinador coordinador;
  Usuario usuario;

public:
  Controlador()
      : usuario(inventario, inventarioCompra), coordinador(inventario) {}
  void run() {
    while (true) {
      cout << "Bienvenido a EAFI-ZON, presione 1 si es un cliente, " << endl;
      cout << "y presione 2 si es coordinador" << endl;
      int opcion;
      cin >> opcion;
      if (opcion == 1)
        usuario.menu_usuario();
      else if (opcion == 2)
        coordinador.menu_coordinador();
      else
        cout << "Opción no válida" << endl;
    }
  }
};

int main() {
  Controlador controlador;
  controlador.run();
  return 0;
}