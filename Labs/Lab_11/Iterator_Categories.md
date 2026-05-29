![alt text](image-1.png)
![alt text](image-2.png)

*Информация с сайта https://en.cppreference.com/cpp/iterator*

В этом списке каждая концепция обладает всеми возможностями предыдущей и новыми, которые указаны.

Краткий перевод всех ключевых концепций:

1) **indirectly_readable** - можно прочитать значение - *it

2) **indirectly_writable** - можно записать значение - *it = value

3) **weakly_incrementable** - можно увеличить (но не обязательно сравнивать) - ++it, it++

4) **input_or_output_iterator** - минимальный набор: увеличение и косвенный доступ - ++it, *it

5) **input_iterator** - чтение, сравнение, однопроходность - ==, !=, *it, ++

6) **forward_iterator** - многопроходность, можно сохранять копии - всё из input + можно пройтись несколько раз

7) **bidirectional_iterato** - движение назад - --it

8) **random_access_iterator** - прыжки по индексам - it + n, it[n], <

9) **contiguous_iterator** - непрерывность в памяти - всё из random_access + гарантия, что элементы лежат подряд
