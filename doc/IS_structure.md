1. IS global registry (modules, libraries for compilation)
2. IS company registry (modules, libraries for compilation contribyted by one Developers Group)
3. IS local registry (libraries for compilation current project)
4. "$ is" command for translate and compile Implementation Schema programs
5. "$ is-cc" command for compile and C++ modules for Implementation Schema programs

Commands:

    $ is init                  - инициализация проекта
    $ is source.is elf.out     - сборка binary из source.is и использованием всех registry
    $ is source.is object.out shared.so la.la lo.lo c-source.cpp - сборка библиотеки в .so, .la, .lo и .cpp для дальнейшей сборки в IS или с помощью других компиляторов
    $ is clean                 - полностью очистить local registry
    $ is add-library source  - добавить в local registry библиотеку
    $ is add-company-library source     - добавить в company registry библиотеку
    $ is-cc cli.cpp              - сборка *.o файла для модулья для global или company registry
    $ is-cc makemodule a.cpp [a_private.cpp [c.cpp [d.cpp]]] - сборка модуля для global или company reigstry
    $ is-cc import-global ./modules/cli   - включение модулья для global reigstry
    $ is-cc import-company ./modules/cli   - включение модулья для company reigstry
    $ is-cc import-local ./modules/cli     - включение модулья для local reigstry
    $ is update company                    - обновить company reigstry для библиотек
    $ is-cc update company                    - обновить company reigstry для модулей
