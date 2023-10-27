Метод https://github.com/lukoshko11/algorithms-and-data-structures/blob/main/sspisok.cpp#L26 работает за О(n) потому что в нем один цикл который зависит от n(в нашем случае индекс)
Метод https://github.com/lukoshko11/algorithms-and-data-structures/blob/main/ConsoleApplication23.cpp#L210 работает также за n, потому что внутри метода вызывается метод getItemByIndex в котором есть цикл зависящий от n
Метод https://github.com/lukoshko11/algorithms-and-data-structures/blob/main/ConsoleApplication23.cpp#L629 работает за О(n^2), внутри функции два цикла, внешний for и внутренний while значит мы получаем n^2, также в конце есть ещё один цикл while, но его n настолько мало по сравнению с n^2 что мы просто не учитываем этот цикл