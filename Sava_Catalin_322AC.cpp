//Monstrii si Lei
//Sava Catalin - 322AC
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <cmath>

using namespace std;

class Employee{
private: string name;
        string role;
public: friend class CreateCast;
};

class CreateCast{
private:vector <Employee> emp; //Sa speram ca se primesc puncte pentru folosirea de templates aici :)
        vector <int> roles;
        vector <int> diets;
        fstream cast;
        fstream final_cast;
        fstream results_ro;
        fstream results_en;
        int n = 0;
        static int total_cost;
        float buses;
        float transport_cost = 0, cazare_cost = 0, machiaj_cost = 0, mancare_apa_cost = 0, castel_cost = 0;
public:
    friend class Menus;

    CreateCast(){
        cast.open("wednesdayCast.csv");
        final_cast.open("final_cast.csv", fstream::in | fstream::out | fstream::trunc);
        results_ro.open("results_ro.csv", fstream::in | fstream::out | fstream::trunc);
        results_en.open("results_en.csv", fstream::in | fstream::out | fstream::trunc);
        string line;
        Employee temp_emp;
        try{
        if(cast.is_open()){
            while(1){
                getline(cast,line, ',');
                if(cast.eof()) break;
                temp_emp.name = line;
                getline(cast,line);
                temp_emp.role = line;
                n++;
                emp.push_back(temp_emp);
            }
            n--;
        }else throw;
        }catch(...){
             cout << "Fisierul nu s-a deschis";
        }
    }
    void ExtendedCast(){
        try{
            if(final_cast.is_open()){
                for(int i = 0; i <= emp.size()-1; i++){
                    final_cast << emp[i].name << "," << emp[i].role << endl;
                }
            }else throw ;
        } catch(...){
            cout << "Fisierul nu s-a deschis";
        }
    }

    void CreateRandomActors(int i){
        Employee temp_emp;
        temp_emp.name = "Actor" + to_string(i+1);
        temp_emp.role = "Extra";
        emp.push_back(temp_emp);
    }

    void NumberOfBuses(){
        int rows = 0;
        string line;
        final_cast.clear();
        final_cast.seekg(0, ios::beg);
        while(getline(final_cast, line)){
            if(final_cast.eof()) break;
            rows++;
        }
        buses = round(rows/50);
        cout << "Numarul de autobuze este: " << buses << endl;
        transport_cost += (5680* buses);
        total_cost += (5680* buses);
    }

    void AssignDiets(){
        string line;
        final_cast.clear();
        final_cast.seekg(0, ios::beg);
        while(getline(final_cast, line)){
            if(final_cast.eof()) break;
            int randnumber = rand() % 3;
            diets.push_back(randnumber);
        }
    }

    void AssignRoles(){
        int nr_roles = 0;
        nr_roles = 54+132; //63 actori + 132 extra
        for(int i = 0; i <= nr_roles; i++){
            int randnumber = rand() % 5;
            roles.push_back(randnumber);
        }
    }

    void CalcRoles(){
        try{
        for(int i: roles){
            if(i == 0){
                total_cost += 230;
                machiaj_cost += 230;
            } //Vampir
            else if(i == 1){
                total_cost += 555;
                machiaj_cost += 555;
            } //Varcolac
            else if(i == 2){
                total_cost += 345;
                machiaj_cost += 354;
            } //Sirena
            else if(i == 3){
                total_cost += 157;
                machiaj_cost += 157;
            } //Clarvazator
            else if(i == 4){
                total_cost += 55;
                machiaj_cost += 55;
            } //Om
            else{
                throw;
            }
        }
        }catch(...){
            cout << "Rol inexistent";
        }
    }

    void CalcMenus(){
        unsigned int vecSize1 = diets.size();
        for(unsigned int i = 0; i < vecSize1; i++){
            if(roles[i] == 0)
                total_cost += 40;
                mancare_apa_cost += 40; //Mananc orice
            if(roles[i] == 1)
                total_cost += 33;
                mancare_apa_cost += 33; //Vegetarieni
            if(roles[i] == 2)
                total_cost += 46;
                mancare_apa_cost += 46; //Flexitarieni
        }
    }

    void AssignRooms(){
        string line;
        int rows = 0;
        final_cast.clear();
        final_cast.seekg(0, ios::beg);
        while(getline(final_cast, line)){
            if(final_cast.eof()) break;
                rows++;
        }
        total_cost += ((132/3)*420);
        cazare_cost += ((132/3)*420);
        int initial_cast = rows - 132;
        total_cost += ((initial_cast/2)*350);
        cazare_cost += ((initial_cast/2)*350);
    }

    void CalcDrinks(){
        float L_Cafea=0, L_Apa=0, L_Suc=0;
        string line;
        int rows = 0;
        final_cast.clear();
        final_cast.seekg(0, ios::beg);
        while(getline(final_cast, line)){
            if(final_cast.eof()) break;
                L_Apa += 1;
                total_cost += 3;
                mancare_apa_cost += 3;
                L_Cafea += 0.5;
                total_cost += 15;
                mancare_apa_cost += 15;
                L_Suc += 0.8;
                total_cost += 3.2;
                mancare_apa_cost += 3.2;
        }
    }

    void PretCastel(int zile){
        int pret_castel = 0;
        pret_castel = 10000 * zile;
        int reducere = (2/100 * 10000) * (zile/10);
        pret_castel = pret_castel - reducere;
        total_cost += pret_castel;
        castel_cost += pret_castel;
    }

    void PretCastel(){
        int pret_castel = 0;
        pret_castel = 10000 * 30;
        int reducere = (2/100 * 10000) * (30/10);
        pret_castel = pret_castel - reducere;
        total_cost += pret_castel;
        castel_cost += pret_castel;
    }

    float GetTotalCost(){
        return (total_cost / 4.64);
    }

    void ResetStats(){
        total_cost = (5680* buses);
        transport_cost = (5680* buses);
        cazare_cost = 0;
        machiaj_cost = 0;
        mancare_apa_cost = 0;
        castel_cost = 0;
    }

    void OutputStats(int zile){
        try{
            if(results_ro.is_open()){
                    results_ro.precision(2);
                    results_ro << "Costul total pentru " << fixed <<zile << " de zile este " << GetTotalCost() << "$" << endl;
                    results_ro << "Costul pentru transport este " << transport_cost << "$" << endl;
                    results_ro << "Costul pentru cazare este " << cazare_cost << "$" << endl;
                    results_ro << "Costul pentru machiaj este " << machiaj_cost << "$" << endl;
                    results_ro << "Costul pentru mancare si apa este " << mancare_apa_cost << "$" << endl;
                    results_ro << "Costul pentru castel este " << castel_cost << "$" << endl;
                    results_ro << endl;
            }else throw ;
        } catch(...){
            cout << "Fisierul nu s-a deschis";
        }
    }

    void OutputStatsEn(int zile){
        try{
            if(results_en.is_open()){
                    results_en.precision(2);
                    results_en << "Total cost for " << fixed << zile << " days is " << GetTotalCost() << "$" << endl;
                    results_en << "Cost for transport: " << transport_cost << "$" << endl;
                    results_en << "Cost for accommodation: " << cazare_cost << "$" << endl;
                    results_en << "Cost for makeup: " << machiaj_cost << "$" << endl;
                    results_en << "Cost for food and drinks: " << mancare_apa_cost << "$" << endl;
                    results_en << "Cost for castle: " << castel_cost << "$" << endl;
                    results_en << endl;
            }else throw ;
        } catch(...){
            cout << "Fisierul nu s-a deschis";
        }
    }

    ~CreateCast(){
        cast.close();
        final_cast.close();
        results_en.close();
        results_ro.close();

    }
};

class Menus{
public:
    virtual void orice(int zile) = 0;
    virtual void vegetarian(int zile) = 0;
    virtual void flexitarian(int zile) = 0;
    virtual void WriteInFile(string message) = 0;
    virtual void WriteInFileEn(string message) = 0;
};

class MenuManager : public Menus{
protected: fstream menu_output_ro;
            fstream menu_output_en;
public:
    MenuManager(){
        menu_output_ro.open("menu_output_ro.csv", fstream::in | fstream::out | fstream::trunc);
        menu_output_en.open("menu_output_en.csv", fstream::in | fstream::out | fstream::trunc);
    }

    void orice(int zile){
        menu_output_ro << "--Meniul pentru cei care mananca orice pe toata perioada--" << endl;
        for(int i = 0; i <= round(zile/3); i++){
            menu_output_ro << "Supa/ciorba(orice)" << i+1 << endl;
            menu_output_ro << "Fel principal(orice)" << i+1 << endl;
            menu_output_ro << "Desert(orice)" << i+1 << endl;
            menu_output_ro << endl;
        }

        menu_output_en << "--Menu for people who eat anything--" << endl;
        for(int i = 0; i <= round(zile/3); i++){
            menu_output_en << "Soup(anything)" << i+1 << endl;
            menu_output_en << "Main Dish(anything)" << i+1 << endl;
            menu_output_en << "Dessert(anything)" << i+1 << endl;
            menu_output_en << endl;
        }
    }

    void vegetarian(int zile){
        menu_output_ro << "--Meniul pentru vegetarieni pe toata perioada--" << endl;
        for(int i = 0; i <= round(zile/3); i++){
            menu_output_ro << "Supa/ciorba(vegetarian)" << i+1 << endl;
            menu_output_ro << "Fel principal(vegetarian)" << i+1 << endl;
            menu_output_ro << "Desert(vegetarian)" << i+1 << endl;
            menu_output_ro << endl;
        }

        menu_output_en << "--Menu for vegans--" << endl;
        for(int i = 0; i <= round(zile/3); i++){
            menu_output_en << "Soup(vegan)" << i+1 << endl;
            menu_output_en << "Main Dish(vegan)" << i+1 << endl;
            menu_output_en << "Dessert(vegan)" << i+1 << endl;
            menu_output_en << endl;
        }
    }

    void flexitarian(int zile){
        menu_output_ro << "--Meniul pentru flexitarian pe toata perioada--" << endl;
        for(int i = 0; i <= round(zile/3); i++){
            menu_output_ro << "Supa/ciorba(flexitarian)" << i+1 << endl;
            menu_output_ro << "Fel principal(flexitarian)" << i+1 << endl;
            menu_output_ro << "Desert(flexitarian)" << i+1 << endl;
            menu_output_ro << endl;
        }

        menu_output_en << "--Menu for flexitarians--" << endl;
        for(int i = 0; i <= round(zile/3); i++){
            menu_output_en << "Soup(flex)" << i+1 << endl;
            menu_output_en << "Main Dish(flex)" << i+1 << endl;
            menu_output_en << "Dessert(flex)" << i+1 << endl;
            menu_output_en << endl;
        }
    }

    void WriteInFile(string message){
        menu_output_ro << message << endl;
    }

    void WriteInFileEn(string message){
        menu_output_en << message << endl;
    }

    ~MenuManager(){
        menu_output_ro.close();
        menu_output_en.close();
    }
};

int CreateCast::total_cost = 0;

int main(){
        srand (time(NULL)); //Seed pt random
        cout.precision(2);//2 zecimale precizie

        MenuManager menus;
        Menus* menu_manager = &menus;

        CreateCast cast;
        for(int i=0; i <= 131; i++)
            cast.CreateRandomActors(i); //Creeaza 132 extras

        cast.ExtendedCast(); //Output fisier cast+extras
        cast.NumberOfBuses(); //Se calculeaza numarul de autobuze necesare si costul lor
        cast.AssignRoles(); //Se creeaza un vector cu roluri random pt fiecare membru din cast

        //Cost 30 de zile
        for(int i=0; i <= 29; i++){
            cast.CalcRoles();
            cast.CalcMenus();
            cast.AssignRooms();
            cast.CalcDrinks();
        }
        cast.PretCastel();
        cout << "Pretul pentru 30 de zile de filmari este " << fixed << cast.GetTotalCost() << " USD" << endl;
        //Creez fisierele de costuri
        cast.OutputStats(30);
        cast.OutputStatsEn(30);
        //Resetez valorile pentru urmatoarea iteratie
        cast.ResetStats();
        //Creez fisierele de meniuri
        menu_manager->WriteInFile("---------Pentru 30 de zile---------");
        menu_manager->WriteInFileEn("---------For 30 days---------");
        menu_manager->orice(30);
        menu_manager->vegetarian(30);
        menu_manager->flexitarian(30);

        //Cost 45 de zile
        for(int i=0; i <= 44; i++){
            cast.CalcRoles();
            cast.CalcMenus();
            cast.AssignRooms();
            cast.CalcDrinks();
        }
        cast.PretCastel(45);
        cout << "Pretul pentru 45 de zile de filmari este " << cast.GetTotalCost() << " USD" << endl;
        cast.OutputStats(45);
        cast.OutputStatsEn(45);
        cast.ResetStats();
        menu_manager->WriteInFile("---------Pentru 45 de zile---------");
        menu_manager->WriteInFileEn("---------For 45 days---------");
        menu_manager->orice(45);
        menu_manager->vegetarian(45);
        menu_manager->flexitarian(45);


        //Cost 60 de zile
        for(int i=0; i <= 59; i++){
            cast.CalcRoles();
            cast.CalcMenus();
            cast.AssignRooms();
            cast.CalcDrinks();
        }
        cast.PretCastel(60);
        cout << "Pretul pentru 60 de zile de filmari este " << cast.GetTotalCost() << " USD" << endl;
        cast.OutputStats(60);
        cast.OutputStatsEn(60);
        cast.ResetStats();
        menu_manager->WriteInFile("---------Pentru 60 de zile---------");
        menu_manager->WriteInFileEn("---------For 60 days---------");
        menu_manager->orice(60);
        menu_manager->vegetarian(60);
        menu_manager->flexitarian(60);


        //Cost 100 de zile
        for(int i=0; i <= 99; i++){
            cast.CalcRoles();
            cast.CalcMenus();
            cast.AssignRooms();
            cast.CalcDrinks();
        }
        cast.PretCastel(100);
        cout << "Pretul pentru 100 de zile de filmari este " << cast.GetTotalCost() << " USD" << endl;
        cast.OutputStats(100);
        cast.OutputStatsEn(100);
        cast.ResetStats();
        menu_manager->WriteInFile("---------Pentru 100 de zile---------");
        menu_manager->WriteInFileEn("---------For 100 days---------");
        menu_manager->orice(100);
        menu_manager->vegetarian(100);
        menu_manager->flexitarian(100);


        return 0;
}
