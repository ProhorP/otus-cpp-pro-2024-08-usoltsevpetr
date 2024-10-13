#include <type_traits>
class File
{
private:
public:
    File() = default;
    ~File() = default;
};

class File2
{
private:
public:
    File2() = default;
    ~File2() = default;
};

class Document
{
private:
public:
    Document() = default;
    Document([[maybe_unused]] File file) {};
    Document([[maybe_unused]] File2 file) {};
    template <typename T,
              std::enable_if_t<std::is_same_v<T, File>, bool> = true>
    T exportFile()
    {
        return {};
    }
    template <typename T,
              std::enable_if_t<std::is_same_v<T, File2>, bool> = true>
    T exportFile()
    {
        return {};
    }
    ~Document() = default;
};

class View
{
private:
    Document doc;

public:
    View() = default;

    template <typename T>
    View(T param) : doc{Document(param)} {}

    template <typename T>
    void importFile(T param) { doc = Document(param); }

    template <typename T>
    T exportFile() { return doc.exportFile<T>(); }

    ~View() = default;
};

int main()
{
    View view(File{});
    view.importFile(File{});
    File file = view.exportFile<File>();
}