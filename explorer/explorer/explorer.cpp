#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
using namespace std;
namespace fs = filesystem;

void createFile(const fs::path& currentDir)
{
    string filename;
    cout << "Введите название нового файла: ";
    cin >> filename;
    ofstream newFile(currentDir / filename);
    if (newFile)
    {
        cout << "Файл успешно создан.\n";
    }
    else
    {
        cerr << "Ошибка создания файла.\n";
    }
}

void deleteFile(const fs::path& currentDir)
{
    string filename;
    cout << "Введите название файла для удаления: ";
    cin >> filename;
    fs::path filePath = currentDir / filename;
    if (fs::remove(filePath))
    {
        cout << "Файл успешно удалён.\n";
    }
    else
    {
        cerr << "Не удалось удалить.\n";
    }
}

void renameFile(const fs::path& currentDir)
{
    string oldFilename, newFilename;
    cout << "Введите название файла для переименования: ";
    cin >> oldFilename;
    cout << "Введите новое название: ";
    cin >> newFilename;
    fs::path oldFilePath = currentDir / oldFilename;
    fs::path newFilePath = currentDir / newFilename;
    try
    {
        fs::rename(oldFilePath, newFilePath);
        cout << "Переименование файла прошло успешно.\n";
    }
    catch (const fs::filesystem_error& e)
    {
        cerr << "Не удалось переименовать файл: " << e.what() << '\n';
    }
}

void moveFile(const fs::path& currentDir)
{
    string filename, targetDir;
    cout << "Введите название файла для перемещения: ";
    cin >> filename;
    cout << "Введите директорию в которую надо перенести: ";
    cin >> targetDir;
    fs::path filePath = currentDir / filename;
    fs::path targetPath = fs::path(targetDir) / filename;
    try
    {
        fs::rename(filePath, targetPath);
        cout << "Файл успешно перемещён.\n";
    }
    catch (const fs::filesystem_error& e)
    {
        cerr << "Не удалось переместить: " << e.what() << '\n';
    }
}

void displayFileContent(const fs::path& currentDir)
{
    string filename;
    cout << "Введите имя файла, который будет отображаться: ";
    cin >> filename;
    fs::path filePath = currentDir / filename;
    ifstream file(filePath);
    if (file)
    {
        string line;
        while (getline(file, line))
        {
            cout << line << '\n';
        }
    }
    else
    {
        cerr << "Не удалось открыть файл.\n";
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    fs::path currentDir = fs::current_path();
    int choice;

    do 
    {
        cout << "\t\t\t\t<---------Простой файловый менеджер--------->\n";
        cout << "\t\t\t\t\t  Директория по умолчанию: \n" << "\t\t\t  " << currentDir << '\n';
        cout << "1. Создать новый файл\n";
        cout << "2. Удалить файл\n";
        cout << "3. Переименовать файл\n";
        cout << "4. Переместить файл\n";
        cout << "5. Отобразить содержимое файла\n";
        cout << "6. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createFile(currentDir);
            break;
        case 2:
            deleteFile(currentDir);
            break;
        case 3:
            renameFile(currentDir);
            break;
        case 4:
            moveFile(currentDir);
            break;
        case 5:
            displayFileContent(currentDir);
            break;
        case 6:
            cout << "Выход...\n";
            break;
        default:
            cout << "Нет такого пункта.\n";
        }
    } while (choice != 6);

    return 0;
}
