
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
class ReplaceTextCommand : public Command
{
protected:
  TXT *current_txt;

public:
  void execute(const string &input) override
  {
    regex replaceTextRegex(R"(sed\s+\-i\s+'s/([^/]+)/([^/]+)/g'\s+[^"]+\.txt)");
    string textToFind, textToReplace;
    if (searchForReplacement(input, replaceTextRegex, textToFind, textToReplace))
    {
      replaceAllSubstrings(current_txt->getfileContent(), textToFind, textToReplace);
    }
  }

  bool searchForReplacement(const string &input, const regex &Regex, string &find, string &replace)
  {
    smatch match;
    if (regex_search(input, match, Regex) && match.size() > 2)
    {
      find = match[1].str();
      replace = match[2].str();
      return true;
    }
    print("No match found.");
    return false;
  }

  void replaceSubstring(string &s, const string &find, const string &replace)
  {
    size_t pos = 0;
    while ((pos = s.find(find, pos)) != string::npos)
    {
      s.replace(pos, find.length(), replace);
      pos += replace.length();
    }
  }

  void replaceAllSubstrings(vector<string> &vec, const string &find, const string &replace)
  {
    for (string &s : vec)
    {
      replaceSubstring(s, find, replace);
    }
  }

  void setTxt(TXT *current_txt)
  {
    this->current_txt = current_txt;
  }
};

class CopyTextCommand : public Command
{
protected:
  TXT *current_txt;

public:
  void execute(const string &input) override
  {
    regex copyTextRegex(R"(cp\s+'([^']+)'(\s+\d+)?\s+[^"]+\.txt)");
    string textToCopy;
    int copyTimes = 1;
    if (searchForCopy(input, copyTextRegex, textToCopy, copyTimes))
    {
      duplicateSubstring(current_txt->getfileContent(), textToCopy, copyTimes);
    }
  }

  bool searchForCopy(const string &input, const regex &Regex, string &text, int &times)
  {
    smatch match;
    if (regex_search(input, match, Regex))
    {
      text = match[1].str();
      if (match.size() > 2 && !match[2].str().empty())
      {
        times = stoi(match[2].str());
      }
      return true;
    }
    print("No match found.");
    return false;
  }

  void duplicateSubstring(vector<string> &vec, const string &text, int times)
  {
    for (string &s : vec)
    {
      size_t pos = s.find(text);
      if (pos != string::npos)
      {
        string toInsert = string(times, ' ') + text; 
        s.insert(pos + text.length(), toInsert);
      }
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
    : text(fileName, filePath, fileContent), Dcommand(new DeleteTextCommand()), AddCommand(new AddTextCommand()),copyTextCommand(new CopyTextCommand()),replaceTextCommand(new ReplaceTextCommand()) {
    textCopy.push_back(text);
    Dcommand->setTxt(&text);
    AddCommand->setTxt(&text);
    copyTextCommand->setTxt(&text);
    replaceTextCommand->setTxt(&text);
  }

  protected:
  TXT text;
  vector<TXT> textCopy;
  DeleteTextCommand* Dcommand;
  AddTextCommand* AddCommand;
  CopyTextCommand* copyTextCommand;
  ReplaceTextCommand* replaceTextCommand;
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
  TXT& copyText(const string &input){
    copyTextCommand->setTxt(&text);
    copyTextCommand->execute(input);
    textCopy.push_back(text);
    return text;
  }
  TXT& replace(const string &input){
    replaceTextCommand->setTxt(&text);
    replaceTextCommand->execute(input);
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
    
    // Adding new text
    print("Adding new text");
    string addInput = R"(echo "New line added" >> example.txt)";
    TXT &addedText = invoker.AddText(addInput);
    print("Content after addition:");
    print(addedText.getfileContent());
    print();

    // Deleting text
    print("Deleting text");
    string delInput = R"(sed -i 's/New line added//g' example.txt)";
    TXT &deletedText = invoker.DeleteText(delInput);
    print("Content after deletion:");
    print(deletedText.getfileContent());
    print();

    // Replacing text
    print("Replacing text");
    string replaceInput = R"(sed -i 's/test/replacement/g' example.txt)";
    TXT &replacedText = invoker.replace(replaceInput);
    print("Content after replacement:");
    print(replacedText.getfileContent());
    print();

    // Copying text
    print("Copying text");
    string copyInput = R"(cp 'Hello, world!' 2 example.txt)";
    TXT &copiedText = invoker.copyText(copyInput);
    print("Content after copying:");
    print(copiedText.getfileContent());
    print();

    // Undo operation after copy
    print("Attempting an undo operation after copy");
    TXT &undoTextAfterCopy = invoker.undo();
    print("Content after undo:");
    print(undoTextAfterCopy.getfileContent());
    print();
}

/*output:
  Adding new text
  Content after addition:
  [Hello, world!, This is a test., New line added]

  Deleting text
  Content after deletion:
  [Hello, world!, This is a test., ]

  Replacing text
  Content after replacement:
  [Hello, world!, This is a replacement., ]

  Copying text
  Content after copying:
  [Hello, world!  Hello, world!, This is a replacement., ]

  Attempting an undo operation after copy
  Content after undo:
  [Hello, world!, This is a replacement., ]
*/