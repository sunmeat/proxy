#include <iostream>
using namespace std;

// Интерфейс базы данных
class Database {
public:
    virtual void query(string query) = 0;
};

// Реализация базы данных
class DatabaseImplementation : public Database {
public:
    void query(string query) override {
        cout << "Выполнение запроса к базе данных...\n";
        cout << query << "\n";
    }
};

// Прокси-класс для базы данных
class DatabaseProxy : public Database {
    DatabaseImplementation* db; // Указатель на реальный объект базы данных
    string username;  // Имя пользователя
    string password;  // Пароль
public:
    DatabaseProxy(string username, string password) : db(nullptr), username(username), password(password) {}

    void query(string query) override {
        authenticate();
        if (db == nullptr) {
            db = new DatabaseImplementation();
        }
        db->query(query);
    }

    void authenticate() {
        // Проверяем, что пользователь имеет правильные учётные данные
        if (username == "admin" && password == "password") {
            cout << "Вы аутентифицированы.\n";
        }
        else {
            cout << "Неверное имя пользователя или пароль.\n";
            throw exception();
        }
    }
};

int main() {
    setlocale(0, "");

    // Создаем прокси-объект базы данных
    auto proxy = new DatabaseProxy("admin", "password");

    // Выполняем запрос к базе данных через прокси
    proxy->query("SELECT * FROM Products");

    // Попытка выполнения запроса без аутентификации
    auto invalid = new DatabaseProxy("invalid", "invalid");
    try {
        invalid->query("DROP DATABASE Store");
    }
    catch(...)
    {
        cout << "Ага, попался!!\n";
    }
}

/*
Код представляет пример использования паттерна
проектирования "Заместитель" (Proxy).

В этом примере создается интерфейс базы данных (Database),
а затем создается его реализация (DatabaseImplementation).
Затем создается прокси-класс для базы данных
(DatabaseProxy), который имеет тот же интерфейс, что и
реализация базы данных, и который содержит указатель
на реальный объект базы данных. Прокси-класс также имеет
дополнительную функциональность, например, аутентификацию
пользователя, которую нужно пройти перед выполнением
запросов к базе данных.

В функции main создается прокси-объект базы данных
с правильным именем пользователя и паролем, и через него
выполняется запрос к базе данных. Затем создается
недопустимый прокси-объект с неверным именем пользователя
и паролем, и при попытке выполнения запроса к базе данных
через этот объект возникает исключение, которое
обрабатывается в блоке catch.

В целом, код хорошо структурирован и четко демонстрирует
использование паттерна "Заместитель". Однако, следует
отметить, что использование указателя в классе прокси
может привести к проблемам с управлением памятью, и это
можно исправить, например, использованием умных
указателей (smart pointers).
*/

// https://refactoring.guru/ru/design-patterns/proxy

/*
Заместитель — это структурный паттерн проектирования,
который позволяет подставлять вместо реальных объектов
специальные объекты-заменители. Эти объекты перехватывают
вызовы к оригинальному объекту, позволяя сделать что-то
до или после передачи вызова оригиналу.
*/