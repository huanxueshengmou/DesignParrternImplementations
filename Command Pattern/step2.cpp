#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <regex>
#include "my_print.cpp"
using namespace std;
using std::shared_ptr;
using std::smatch;
using std::string;
using std::vector;

class TXT
{
public:
  TXT(const TXT& other) 
  : fileName(other.fileName)
  , filePath(other.filePath)
  , fileContent(other.fileContent)
  , fileSize(other.fileSize)
   {}
  TXT& operator=(const TXT& other) {
        if (this != &other) {
            fileName = other.fileName;
            filePath = other.filePath;
            fileContent = other.fileContent;
            fileSize = other.fileSize;
        }
        return *this;
    }
  TXT(string fileName, string filePath, vector<string> fileContent)
  {
    this->fileName = fileName;
    this->filePath = filePath;
    this->fileContent = fileContent;
  }

protected:
  size_t fileSize;
  string fileName;
  vector<char32_t> fileAddress;
  string filePath;
  vector<string> fileContent;

private:
  template <typename T>
  size_t vector_memory_usage(const vector<T> &vec)
  {
    size_t pointer_size = sizeof(void *);
    size_t vector_overhead = 3 * pointer_size;
    return vector_overhead;
  }

  size_t string_memory_usage(const string &str)
  {
    size_t pointer_size = sizeof(void *);
    size_t size_size = sizeof(size_t);
    size_t capacity_size = sizeof(size_t);
    size_t string_overhead = pointer_size + size_size + capacity_size;
    return string_overhead + str.capacity();
  }

  size_t total_memory_usage(const vector<std::string> &vec)
  {
    size_t total_usage = vector_memory_usage(vec);
    for (const auto &str : vec)
    {
      total_usage += string_memory_usage(str);
    }
    return total_usage;
  }
  void commputeFileSize()
  {
    fileSize = total_memory_usage(fileContent);
  }

public:
  string getPath()
  {
    return filePath;
  };
  vector<string> &getfileContent()
  {
    return fileContent;
  }
  size_t getFileSize()
  {
    commputeFileSize();
    return fileSize;
  }

protected:
  vector<char32_t> getAddress()
  {
    return fileAddress;
  };
};
class Command
{
public:
  virtual void execute(const string &input) = 0;
};
class AddTextCommand : Command
{
protected:
  TXT *current_txt;

public:
  string searchRegex(const string &input, regex Regex)
  {
    smatch match;
    if (regex_search(input, match, Regex))
    {
      if (match.size() > 1)
      {
        string content = match[1].str();
        return content;
      }
      else
      {
        print("Match found, but no content extracted.");
        return "";
      }
    }
    else
    {
      print("No match found.");
      return "";
    }
  }
  void execute(const string &input) override
  {
    regex addTextRegex(R""(echo\s+"([^"]*)"\s*>>\s*[^"]+\.txt)"");
    string contentToAdd = searchRegex(input, addTextRegex);
    if (!contentToAdd.empty())
    {
      current_txt->getfileContent().push_back(contentToAdd);
    }
  }
  void setTxt(TXT *current_txt)
  {
    this->current_txt = current_txt;
  }
};
class DeleteTextCommand : Command
{
protected:
  TXT *current_txt;

public:
  string searchRegex(const string &input, regex Regex)
  {
    smatch match;
    if (regex_search(input, match, Regex))
    {
      if (match.size() > 1)
      {
        string content = match[1].str();
        return content;
      }
      else
      {
        print("No match found.");
        return "";
      }
    }
    return "";
  }
  void execute(const string &input) override
  {
    regex deleteTextRegex(R"(sed\s+\-i\s+'s/([^/]+)/.*?/g'\s+[^"]+\.txt)");
    string contentToDelete = searchRegex(input, deleteTextRegex);
    if (!contentToDelete.empty())
    {
      removeAllSubstrings(current_txt->getfileContent(), contentToDelete);
    }
  }

  void removeSubstring(string &s, const string &str)
  {
    size_t pos = s.find(str);
    if (pos != string::npos)
    {
      s.erase(pos, str.length());
      removeSubstring(s, str);
    }
  }
  void removeAllSubstrings(vector<string> &vec, const string &str)
  {
    for (string &s : vec)
    {
      removeSubstring(s, str);
    }
  }
  void setTxt(TXT *current_txt)
  {
    this->current_txt = current_txt;
  }
};

class Invoker{
  public:
  Invoker(std::string fileName, std::string filePath, std::vector<std::string> fileContent)
    : text(fileName, filePath, fileContent), Dcommand(new DeleteTextCommand()), AddCommand(new AddTextCommand()) {
    textCopy.push_back(text);
    Dcommand->setTxt(&text);
    AddCommand->setTxt(&text);
  }

  protected:
  TXT text;
  vector<TXT> textCopy;
  DeleteTextCommand* Dcommand;
  AddTextCommand* AddCommand;
  public:
  void init(TXT&text){
    this->text=text;
    textCopy={};
    textCopy.push_back(text);
    Dcommand=new DeleteTextCommand();
    AddCommand=new AddTextCommand();
  }
  TXT& DeleteText(const string &input){
    Dcommand->setTxt(&text);
    Dcommand->execute(input);
    textCopy.push_back(text);
    return text;
  }
  TXT& AddText(const string &input){
    AddCommand->setTxt(&text);
    AddCommand->execute(input);
    textCopy.push_back(text);
    return text;
  }
  TXT& saveText(){
    if(!textCopy.empty())
    text=textCopy.back();
    textCopy={};
    return text;
  }
  TXT& undo(){
    if(textCopy.empty())return text;
    textCopy.pop_back();
    text=textCopy.back();
    return text;
  }
};

int main()
{
    vector<string> initialContent = {"Hello, world!", "This is a test."};
    Invoker invoker("example.txt", "/path/to/example.txt", initialContent);
    print("Adding new text");
    string addInput = R"(echo "New line added" >> example.txt)";
    TXT &addedText = invoker.AddText(addInput);
    print("Content after addition:");
    print(addedText.getfileContent());
    print();
    string delInput = R"(sed -i 's/New line added//g' example.txt)";
    TXT &deletedText = invoker.DeleteText(delInput);
    print("Deleting text");
    print("Content after deletion:");
    print(deletedText.getfileContent());
    print();
    TXT &undoText = invoker.undo();
    print("Attempting an undo operation");
    print("Content after undo:");
    print(undoText.getfileContent());
}
/*output:
  Adding new text
  Content after addition:
  [Hello, world!, This is a test., New line added]

  Deleting text
  Content after deletion:
  [Hello, world!, This is a test., ]

  Attempting an undo operation
  Content after undo:
  [Hello, world!, This is a test., New line added]
*/