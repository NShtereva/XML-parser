# XML парсер

Да се реализира програма, реализираща четене и операции с XML файлове. 

Характеристиките на XML елементите, поддържани от програмата, да се ограничат до:
  - идентификатор на елемента
  - списък от атрибути и стойности
  - списък от вложени елементи или текст

Да се поддържат уникални идентификатори на всички елементи по следния начин:
  - Ако елементът има поле "id" във входния файл и стойността му е уникална за всички елементи от файла, да се ползва тази стойност.
  - Ако елементът има поле "id" във входния файл, но стойността му не е уникална за всички елементи от файла, за идентификатор да се ползва тази стойност, към
която е слепен подходящ низ, който да допълни идентификатора до уникален такъв (например, ако два елемента имат поле id="1", то единият да получи 
id="1_1", а другият – id="1_2").
  - Ако елементът няма поле "id" във входния файл, да му се присъедини уникален идентификатор, генериран от програмата.

След като приложението отвори даден файл, то трябва да може да извършва посочените по-долу операции, в допълнение на общите операции (open, close, save, saveas, help
и exit):
  - print - Извежда на екрана прочетената информация от XML файла (в рамките на посочените по-горе ограничения за поддържаната информация). Печатането да е XML коректно и да е “красиво”, т.е. да е форматирано визуално по подходящ начин (например, вложените елементи да са по-навътре)
  - select < id > < key > - Извежда стойност на атрибут по даден идентификатор на елемента и ключ на атрибута
  - set < id > < key > < value> - Присвояване на стойност на атрибут 
  - children < id > - Списък с атрибути на вложените елементи
  - child < id > < n > - Достъп до n-тия наследник на елемент
  - text < id > - Достъп до текста на елемент
  - delete < id > < key > - Изтриване на атрибут на елемент по ключ
  - newchild < id > - Добавяне на НОВ наследник на елемент. Новият елемент няма никакви атрибути, освен идентификатор
  - xpath < id > < XPath > - операции за изпълнение на прости XPath 2.0 заявки към даден елемент, която връща списък от XML елементи

## Минимални изисквания за поддържаните XPath заявки
Примерите по-долу са върху следния прост XML низ:
```
<people>
  <person id="0">
    <name>John Smith</name>
    <address>USA</address>
  </person>
  <person id="1">
    <name>Ivan Petrov</name>
    <address>Bulgaria</address>
  </person>
</people>

```
  - да поддържат оператора / (например "person/address" връща списък с всички адреси във файла)
  - да поддържат оператора [] (например "person/address[0]" връща адреса на първия елемент във файла)
  - да поддържат оператора @ (например "person(@id)" дава списък с атрибутите id на всички елементи във файла)
  - Оператори за сравнение = (например "person(address='USA')/name" дава списък с имената на всички елементи, чиито адреси са точно равни на "USA")

Забележка: За проекта не е позволено използването на готови библиотеки за работа с XML. Целта на проекта е да се упражни работата със структурирани текстови файлове, а 
не толкова със самия XML. 

Внимание: Не се изисква осигуряване на всички условия в XML и XPath спецификациите! Достатъчно е файловете да имат основните характеристики на XML (както файла в горния пример, който всъщност не е валиден XML), а завките да имат основните характеристики на XPath. 

Бонуси:
  - да се реализират XML namespaces
  - да се реализират различните XPath оси (ancestor, child, parent, descendant,...)
  
# Работа с командния ред
Вашата програма трябва да позволява на потребителя да отваря файлове (open), да извършва върху тях някакви операции, след което да записва промените обратно в 
същия файл (save) или в друг, който потребителят посочи (saveas). Трябва да има и опция за затваряне на файла без записване на промените (close).

За да предостави на потребителя възможност да укаже каква операция да се изпълни, програмата трябва да работи в интерактивен команден режим: при стартиране, тя 
подканва потребителя да въведе едноредови команди и след това в зависимост от въведените команди да ги изпълнява. Командите могат да имат нула, един или повече 
параметри, които се изреждат един след друг, разделени с един или няколко интервала. Някои от командите може да изискват допълнително въвеждане на информация при 
изпълнението си.

При отваряне на даден файл, неговото съдържание трябва да се зареди в паметта, след което файлът се затваря. Всички промени, които потребителят направи след това трябва да се пазят в паметта, но не трябва да се записват обратно, освен ако потребителят изрично не yкаже това. При изход, програмата трябва да подсеща потребителя дали желае да запише последните промени във файла. Подсещането да се извежда само ако след последното записване е изпълнена операция, която променя данните в паметта.

Бонус: Ако желаете, можете да реализирате възможност, при която текущото състояние на паметта се записва във временен файл за възстановяване (recovery file) като защита при евентуално прекратяване на програмата при грешка. При отваряне на файл, програмата да проверява за наличие на файл за възстановяване и да предлага на 
потребителя да избере дали данните от него да бъдат възстановени или пренебрегнати.

Във всеки от проектите има посочен конкретен файлов формат, с който програмата трябва да работи. Това означава, че:
  1. програмата трябва да може да чете произволен валиден файл от въпросния 
формат;
  2. когато записва данните, програмата трябва да създава валидни файлове във 
въпросния формат.

Освен ако не е указано друго, всяка от командите следва да извежда съобщение, от което да е ясно дали е успяла и какво е било направено.

Дадените по-долу команди трябва да се поддържат от всеки от проектите. Под всяка от тях е даден пример за нейната работа:

## Open
Зарежда съдържанието на даден файл. Ако такъв не съществува, се създава нов с празно съдържание.

След като файлът бъде отворен и се прочете, той се затваря и програмата вече не трябва да работи с негo, освен ако потребителят не поиска да запише обратно 
направените промени (както е указано в командите Save и Save As по-долу), в който случай файлът трябва да се отвори отново за запис.

Ако при зареждането на данните, програмата открие грешка, тя трябва да изведе подходящо съобщение за грешка и да прекрати своето изпълнение.

Пример:
```
> open C:\Temp\file.xml
Successfully opened file.xml
```
## Close
Затваря текущо отворения файл. Командата се изпълнява успешно само ако има текущ отворен файл. Затварянето изчиства текущо заредената информация и след това 
програмата не може да изпълнява други команди, освен отваряне на файл (Open).

Пример:
```
> close
Successfully closed file.xml
```
## Save
Записва направените промени обратно в същия файл, от който са били прочетени данните. Командата се изпълнява успешно само ако има текущ отворен файл.

Пример:
```
> save
Successfully saved file.xml 
```
## Save As
Записва направените промени във файл, като позволява на потребителя да укаже неговия път. Командата се изпълнява успешно само ако има текущ отворен файл.

Пример:
```
> saveas "C:\Temp\another file.xml"
Successfully saved another file.xml
```
## Help
Извежда кратка информация за поддържаните от програмата команди.

Пример:
```
> help
The following commands are supported:
open <file>     opens <file>
close           closes currently opened file
save            saves the currently open file
saveas <file>   saves the currently open file in <file>
help            prints this information
exit            exists the program
```
## Exit
Излиза от програмата. Ако има незаписани промени, предлага на потребителя да избере затваряне с пренебрегване на промените (Close) или записване (Save или Save As).
```
> exit
You have an open file with unsaved changes, please select close or save first.
> close
Successfully closed file.xml
> exit
Exiting program...
```
