class File
{
private:
public:
    File() = default;
    ~File() = default;
};

class Document
{
private:
public:
    Document() = default;
    Document([[maybe_unused]] File file) {};
    File exportFile() { return {}; };
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
    T exportFile() { return doc.exportFile(); }

    ~View() = default;
};

int main()
{
    View view(File{});
    view.importFile(File{});
    File file = view.exportFile<File>();
}