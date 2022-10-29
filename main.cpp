#include <iostream>
#include<vector>
#include <algorithm>

class Author{
    std::string name;
    std::string gender;
    bool alive;
public:
    Author(const std::string& name_, const std::string& gender_, bool alive_) : name{name_}, gender{gender_}, alive{alive_} {
        std::cout << "Constr de initializare Author\n";
    }
//    Author(const Author& other) : name{other.name}, gender{other.gender}, alive{other.alive} {
//        std::cout << "Constr de copiere Author\n";
//    }
//
//    Author& operator=(const Author& other) {
//        std::cout << "Operator= de copiere Author\n";
//        name = other.name;
//        gender = other.gender;
//        alive = other.alive;
//        return *this;
//    }

    friend std::ostream& operator<<(std::ostream& os, const Author& author) {
        os << "Name: " << author.name << ", gender: " << author.gender << ", alive: " << author.alive << "\n";
        return os;
    }

/*    ~Author() {
        std::cout << "Destr Author\n";
    }*/
};

class Publisher{
    std::string name;
    std::vector<Author> authors;

public:
    void add_author(Author author){
        authors.push_back(author);
    }
    std::string getName() const { return name; }
    Publisher(const std::string& name_, const std::vector<Author>& authors_) : name{name_}, authors{authors_} {
        std::cout << "Constr de inițializare Publisher\n";
    }
    Publisher(const Publisher& other) : name{other.name},authors{other.authors}  {
        std::cout << "Constr de copiere Publisher\n";
    }
    Publisher& operator=(const Publisher& other) {
        std::cout << "Operator= de copiere Publisher\n\n";
        name = other.name;
        authors = other.authors;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Publisher& publisher) {
        os << "Name: " << publisher.name << "\n";
        for(const auto& author : publisher.authors)
            os << "Author: " << author << "\n";
        return os;
    }
    ~Publisher() {
//        std::cout << "Destr Publisher\n";
    }
};

enum class Genre{Fiction, Nonfiction, Drama, Poetry, Folktale};

class Book{
protected:
    std::string title;
    Author author;
    Publisher publisher;
    float price;
    Genre genre;
    int year;
public:
    std::string getTitle() const { return title; }
    Genre getGenre() const { return genre; }

    Book(const std::string& title_, const Author& author_, const Publisher& publisher_,float price_,
         const Genre& genre_, int year_) : title{title_}, author{author_},
                                            publisher{publisher_},
                                            price{price_}, genre{genre_},
                                            year{year_} {
        std::cout << "Constr de initializare Book\n\n";
    }
    friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << "Title: " << book.title << ", Author: " << book.author <<
        "Publisher: " << book.publisher.getName() << ", Price: " << book.price <<
        ", Genre: " << static_cast<int>(book.genre) << ", Year: " << book.year << "\n";
        return os;
    }
};

class Library{
    std::string name;
    std::vector<Book> books;
public:
    void add_book(Book book){
        books.push_back(book);
    }

    auto find(std::string title) const {
        auto title_match_fn = [title](auto book) {
            return book.getTitle() == title;
        };
        auto it = find_if(begin(books), end(books), title_match_fn);
        if (it == end(books)) std::cout << "Book unavailable\n";
        else std::cout << "Book available\n";
        return it;
    }

    std::vector<Book> filter_by_genre(Genre genre) const {
        std::vector<Book> new_books;
        auto genre_match_fn = [genre](auto book) {
            return book.getGenre() == genre;
        };
        copy_if(begin(books), end(books), std::back_inserter(new_books), genre_match_fn);
        return new_books;
    }

    void remove_book(const std::string& title){
        auto it = find(title);
        if(it != books.end()) books.erase(it);
        else std::cout << "Book not found!\n";
    }
    Library(const std::string& name_, const std::vector<Book>& books_) : name{name_}, books{books_} {
        std::cout << "Constr de initializare Library\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Library& library) {
        os << "Name: " << library.name << " " << "Shelf: " << "\n";
        for(const auto& book : library.books)
            os << "Book: " << book << "\n";
        return os;
    }
};

int main() {

    Author eminescu("Mihai Eminescu", "male", false);
    std::cout << eminescu;
    Author creanga("Ion Creanga", "male", false);
    std::cout << creanga;
    Author braniste("Lavinia Braniste", "female", true);
    std::cout << braniste;

    Publisher nemira("Nemira", {eminescu});
    nemira.add_author(braniste);
    std::cout << nemira;


    Book b1("Luceafarul", eminescu, nemira, 25.3f, Genre::Poetry, 1987);
    Book b2("Ion", braniste, nemira, 25.3f, Genre::Fiction, 1987);


    Library l("lalala", {b1});
    l.add_book(b2);
    l.find("Ion");

    std::vector<Book> Fiction_books = l.filter_by_genre(Genre::Fiction);
    for (const Book& book: Fiction_books) std::cout << book <<" ";

    l.remove_book("Ion");
    l.remove_book("Iona");

    std::cout<<l;

    return 0;
}
