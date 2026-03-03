#include <vector>
#include <string>
#include <functional>
#include <iostream>
using namespace std;

template <class T> class MyPipeline{
    private: 

        struct Step //Представление шага
        {
            string name;
            function<T(T)> func; //Вызываемый объект, который принимает (T) и возвращает <T...>
        };

        vector <Step> steps; //Хранит все шаги конвейера
        
    public:
        //4.1. Базовые методы
        MyPipeline() {}

        size_t size() const{
            return steps.size();
        }

        bool empty() const{
            return steps.empty();
            /*if (steps.size()==0) {
                return true;
            } else {
                return false;
            }*/
        }

        void clear() {
            steps.clear();
        }

        //4.2. Добавление шага
        template <class F> void addStep(const string& name, F func) {

            if (name.empty()) { throw invalid_argument ("The name is empty");}

            Step newStep; //Создаём новый шаг
            newStep.name=name;
            newStep.func=func;
            steps.push_back(newStep); //Добавляем созданный шаг в конец вектора
        };

        //4.3. Удаление шага
        void removeStep(size_t index) {

            if (index>=steps.size()){throw out_of_range("Index is out of range");}

            steps.erase(steps.begin()+index); //Удаление шага с нужным индексом
        }

        //4.4. Запуск конвейера
        T run(T value) const {
            
            if (steps.empty()) {return value;}

            for (int i=0; i<steps.size(); i++){ //Последовательно применяем все шаги к value
                value=steps[i].func(value);
            }

            return value;
        }

        //4.5. Трассировка
        vector<T> trace(T value) const {
            if (steps.empty()) {return {};} 

            vector <T> values;

            for (int i=0; i<steps.size(); i++){ //Последовательно применяем все шаги к value
                value=steps[i].func(value);
                values.push_back(value);
            }

            return values;
        }

        //Перегрузка <<
        template <class U> friend ostream& operator<<(ostream& os, const MyPipeline<U>& pipe);
        /*template <clas U> - т.к. operator<< это отдельная функция, 
        которая должна уметь работать с любым типом MyPipeLine;
        friend - даёт доступ operator<< к private полям;
        ostream - класс «потока вывода»;
        ostream& os - Output Stream*/
};

// 5. Вывод в поток. Перегрузить operator<<
template <class T>
ostream& operator<<(ostream& os, const MyPipeline<T>& pipeline) {
    
    os << "Pipeline with " << pipeline.steps.size() << " steps:" <<endl; //Заголовок

    for (int i = 0; i < pipeline.steps.size(); i++) {
        os << i << ") " << pipeline.steps[i].name <<endl;
    }

    return os; 
}