#include "../core/unit_test.h"
#include "container/linked_list.h"

static void fill_list(LinkedList<int>& list);

static void print_list(std::ofstream& file, const LinkedList<int>& list);

void linked_list_unit_test() {
    UnitTest test("LinkedList");

    test.Run("Push()", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        print_list(file, list);
    });

    test.Run("Head()", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        file << list.Head();
    });

    test.Run("Head() - Exception", [](std::ofstream& file) {
        const LinkedList<int> list;
        file << list.Head();
    });

    test.Run("Tail()", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        file << list.Tail();
    });

    test.Run("Tail() - Exception", [](std::ofstream& file) {
        const LinkedList<int> list;
        file << list.Tail();
    });

    test.Run("Pop()", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        for (int i = 0; i < 8; i++) list.Pop();
        print_list(file, list);
    });

    test.Run("Pop() - All", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        for (int i = 0; i < 16; i++) list.Pop();
        print_list(file, list);
    });


    test.Run("Pop() - Out of index", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        for (int i = 0; i < 17; i++) {
            try {
                list.Pop();
            } catch (const std::exception& e) {
                file << e.what() << std::endl;
            }
        }
        print_list(file, list);
    });

    test.Run("TryPop()", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        for (int i = 0; i < 8; i++) list.TryPop();
        print_list(file, list);
    });

    test.Run("TryPop() - All", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        for (int i = 0; i < 16; i++)
            file << (list.TryPop() ? "true" : "false") << std::endl;
        print_list(file, list);
    });

    test.Run("TryPop() - Out of index", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        for (int i = 0; i < 17; i++)
            file << (list.TryPop() ? "true" : "false") << std::endl;
        print_list(file, list);
    });

    test.Run("Pop(number)", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        list.Pop(8);
        print_list(file, list);
    });

    test.Run("Pop(number) - All", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        list.Pop(16);
        print_list(file, list);
    });

    test.Run("Pop(number) - Out of index", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        try {
            list.Pop(24);
        } catch (const std::runtime_error& e) {
            file << e.what() << std::endl;
        }
        print_list(file, list);
    });

    test.Run("TryPop(number)", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        file << "Result: " << list.TryPop(8) << std::endl;;
        print_list(file, list);
    });

    test.Run("TryPop(number) - All", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        file << "Result: " << list.TryPop(16) << std::endl;;
        print_list(file, list);
    });

    test.Run("TryPop(number) - Out of index", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        file << "Result: " << list.TryPop(24) << std::endl;;
        print_list(file, list);
    });

    test.Run("PopTail()", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        for (int i = 0; i < 8; i++) list.PopTail();
        print_list(file, list);
    });

    test.Run("PopTail() - All", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        for (int i = 0; i < 16; i++) list.PopTail();
        print_list(file, list);
    });

    test.Run("PopTail() - Out of index", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        for (int i = 0; i < 17; i++) {
            try {
                list.PopTail();
            } catch (const std::runtime_error& e) {
                file << e.what() << std::endl;
            }
        }
        print_list(file, list);
    });

    test.Run("TryPopTail()", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        for (int i = 0; i < 8; i++)
            file << (list.TryPopTail() ? "true" : "false") << std::endl;
        print_list(file, list);
    });

    test.Run("TryPopTail() - All", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        for (int i = 0; i < 16; i++)
            file << (list.TryPopTail() ? "true" : "false") << std::endl;
        print_list(file, list);
    });

    test.Run("TryPopTail() - Out of index", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        for (int i = 0; i < 17; i++)
            file << (list.TryPopTail() ? "true" : "false") << std::endl;
        print_list(file, list);
    });

    test.Run("Remove(index, number) - Head", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        list.Remove(0, 8);
        print_list(file, list);
    });

    test.Run("Remove(index, number) - Center", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        list.Remove(4, 8);
        print_list(file, list);
    });

    test.Run("Remove(index, number) - Tail", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        list.Remove(8, 8);
        print_list(file, list);
    });

    test.Run("Remove(index, number) - Exception 1", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        try {
            list.Remove(0, 24);
        } catch (const std::runtime_error& e) {
            file << e.what() << std::endl;
        }
        print_list(file, list);
    });

    test.Run("Remove(index, number) - Exception 2", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        try {
            list.Remove(8, 24);
        } catch (const std::runtime_error& e) {
            file << e.what() << std::endl;
        }
        print_list(file, list);
    });

    test.Run("Remove(index, number) - Exception 3", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        try {
            list.Remove(24, 24);
        } catch (const std::runtime_error& e) {
            file << e.what() << std::endl;
        }
        print_list(file, list);
    });

    test.Run("TryRemove(index, number) - Head", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        file << "Result: " << list.TryRemove(0, 8) << std::endl;
        print_list(file, list);
    });

    test.Run("TryRemove(index, number) - Center", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        file << "Result: " << list.TryRemove(4, 8) << std::endl;
        print_list(file, list);
    });

    test.Run("TryRemove(index, number) - Tail", [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        file << "Result: " << list.TryRemove(8, 8) << std::endl;
        print_list(file, list);
    });

    test.Run("TryRemove(index, number) - Out of index 1",
             [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        file << "Result: " << list.TryRemove(0, 24) << std::endl;
        print_list(file, list);
    });

    test.Run("TryRemove(index, number) - Out of index 2",
             [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        file << "Result: " << list.TryRemove(8, 24) << std::endl;
        print_list(file, list);
    });

    test.Run("TryRemove(index, number) - Out of index 3",
             [](std::ofstream& file) {
        LinkedList<int> list;
        fill_list(list);
        file << "Result: " << list.TryRemove(24, 24) << std::endl;
        print_list(file, list);
    });
}

static void fill_list(LinkedList<int>& list) {
    for (int i = 1; i <= 16; i++) list.Push(i);
}

static void print_list(std::ofstream& file, const LinkedList<int>& list) {
    /* Print all elements */
    for (const int n : list) file << n << std::endl;

    /* Print the head and the tail */
    file << "---" << std::endl;
    try {
        file << "Head: " << list.Head() << std::endl;
    } catch (std::exception& e) {
        file << e.what() << std::endl;
    }
    try {
        file << "Tail: " << list.Tail() << std::endl;
    } catch (std::exception& e) {
        file << e.what() << std::endl;
    }
}