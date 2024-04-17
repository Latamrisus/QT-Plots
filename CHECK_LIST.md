# Чек-лист для проверки
Ниже приведён чек-лист, на который вы можете опираться при выполнении задания. 
**Заполнять его не нужно, т.к. это чек-лист для проверяющего и заполняться он будет на защите работы.**

Требования:

- [x] Собирается на Qt 5.12.12.
- [x] Имеется \*.pro файл.
- [x] Пользовательский интерфейс описывается кодом (без использования .ui/QML).
- [x] Не используется STL.
- [x] В программе должен быть реализованы класс MainWindow, хранящий виджеты приложения, и класс Plot, отвечающий за формирование данных для их дальнейшей визуализации. Классы должны быть описаны в .h файлах,а  реализация их методов – .cpp файлах. Создавать свои файлы (.h/.cpp) со вспомогательным кодом не запрещено.

Функционал:

1. Просмотр графика функции
- [x] sinc(distance_from_zero)
- [x] sinc(x)\*sinc(z)
- [x] Функция выбирается при помощи RadioButton.

2. Группировка и внешний вид
- [x] Все настройки сгруппированы по смыслу.
- [x] Все названия поясняют настройки.
- [x] При изменении размера окна, настройки не изменяются в размерах, изменяет размеры только график.

3. Градиент цветов
- [x] Минимум 2 градиента.
- [x] Хотя бы один из градиентов должен быть задан через опорные значения цветов.
- [x] Градиент должен запоминаться для каждого из двух графиков.

4. Выбор точки на графике
- [x] Точка, выбранная нажатием левой кнопки мышки по графику, должна быть выделена, и над ней должны выводиться координаты.
- [-] В StatusBar окна должны выводиться эти же координаты.
- [x] Возможность выделения точки должна быть отключаема через настройки.

5. Выбор диапазона отображаемых значений и количества шагов
- [x] Начальный диапазон по осям \[-10, 10].
- [-] Количество шагов: 50.
- [+-] Значения отображаемого диапазона и шага должны отображаться в пользовательском интерфейсе рядом с соответствующей настройкой.
- [x] Через GUI должна быть возможность менять диапазон осям x и z с обеих сторон, “урезая” отображаемый график. Это не должно приводить к пересчёту данных.
- [x] Через GUI должна быть возможность менять количество шагов по каждой оси графика. Данные в этом случае пересчитываются.

6. Настройки отображения графика
- [x] Должен быть CheckBox, отвечающий за отображение сетки.
- [x] Должен быть CheckBox, отвечающий за отображение надписей.
- [x] Должен быть CheckBox, отвечающий за отображение границ надписей (активный только при включенном отображении надписей).

7. Возможность сохранения настроек
- [x] Настройки должны сохраняться в .ini файл, расположенный рядом с исполняемым файлом
- [-] Настройки автоматически загружаются при запуске программы.
- [-] Программа должна проверять прочитанные настройки, и игнорировать некорректные значения (а не падать).
- [+-] Должна быть возможность сохранения и загрузки настроек через: MenuBar, Toolbar и Shortcuts.
- [-] При наведении на опции (как в MenuBar, так и в ToolBar) в StatusBar должна выводиться подсказка StatusTip.

8. \[Бонусные баллы] Перевод всего отображаемого в интерфейсе текста на несколько языков. 
- [ ] Должны быть реализованы хотя бы: английский и русский. 
- [ ] Должна быть возможность переключить язык через меню, в меню язык всегда называется на своём языке и не переводится. 
- [ ] Язык сохраняется вместе с другими настройками. 
- [ ] Язык по умолчанию – выбирается в соответствии с языком системы.

