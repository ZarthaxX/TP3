#include "gtest-1.8.1/gtest.h"
#include "../src/modulos_basicos/string_map.h"

TEST(string_map_test, asignar) {
    string_map<int> singleton;
    singleton.Definir("hola", 1);

    ASSERT_EQ(singleton.Significado("hola"), 1);
    int a = singleton.Claves().count("hola");
    ASSERT_EQ(a, 1);
}

TEST(string_map_test, obtener) {
    string_map<int> sin_prefijos;
    string_map<int> con_prefijos;

    sin_prefijos.Definir("hola", 1);
    sin_prefijos.Definir("chau", 2);
    sin_prefijos.Definir("adios",  3);

    con_prefijos.Definir("c",  1);
    con_prefijos.Definir("casa", 2);
    con_prefijos.Definir("casona", 3);

    ASSERT_EQ(sin_prefijos.Significado("hola"), 1);
    ASSERT_EQ(sin_prefijos.Significado("chau"), 2);
    ASSERT_EQ(sin_prefijos.Significado("adios"), 3);

    ASSERT_EQ(con_prefijos.Significado("c"), 1);
    ASSERT_EQ(con_prefijos.Significado("casa"), 2);
    ASSERT_EQ(con_prefijos.Significado("casona"), 3);
}

TEST(string_map_test, redefinir) {
    string_map<int> con_prefijos;

    con_prefijos.Definir("c",  1);
    con_prefijos.Definir("casa", 2);
    con_prefijos.Definir("casona", 3);

    con_prefijos.Definir("c",  2);
    ASSERT_EQ(con_prefijos.Significado("c"), 2);
    con_prefijos.Definir("c",  3);
    ASSERT_EQ(con_prefijos.Significado("c"), 3);
}

TEST(string_map_test, definido) {
    string_map<int> vacio;
    string_map<int> sin_prefijos;
    string_map<int> con_prefijos;

    sin_prefijos.Definir("hola", 1);
    sin_prefijos.Definir("chau", 2);
    sin_prefijos.Definir("adios",  3);

    con_prefijos.Definir("c",  1);
    con_prefijos.Definir("casa", 2);
    con_prefijos.Definir("casona", 3);

    ASSERT_FALSE(vacio.Definido("a") == 1);
    ASSERT_FALSE(vacio.Definido("aaaa") == 1);
    ASSERT_FALSE(vacio.Definido("adios") == 1);

    ASSERT_TRUE(sin_prefijos.Definido("hola") == 1);
    ASSERT_TRUE(sin_prefijos.Definido("chau") == 1);
    ASSERT_TRUE(sin_prefijos.Definido("adios") == 1);

    ASSERT_FALSE(sin_prefijos.Definido("ho") == 1);
    ASSERT_FALSE(sin_prefijos.Definido("h") == 1);
    ASSERT_FALSE(sin_prefijos.Definido("hol") == 1);

    ASSERT_TRUE(con_prefijos.Definido("c") == 1);
    ASSERT_TRUE(con_prefijos.Definido("casa") == 1);
    ASSERT_TRUE(con_prefijos.Definido("casona") == 1);
    ASSERT_FALSE(con_prefijos.Definido("ca") == 1);
    ASSERT_FALSE(con_prefijos.Definido("cas") == 1);
    ASSERT_FALSE(con_prefijos.Definido("caso") == 1);
}

TEST(string_map_test, claves) {
    string_map<int> vacio;
    string_map<int> sin_prefijos;
    string_map<int> con_prefijos;

    sin_prefijos.Definir("hola", 1);
    sin_prefijos.Definir("chau", 2);
    sin_prefijos.Definir("adios",  3);

    con_prefijos.Definir("c",  1);
    con_prefijos.Definir("casa", 2);
    con_prefijos.Definir("casona", 3);

    ASSERT_FALSE(vacio.Claves().count("a") == 1);
    ASSERT_FALSE(vacio.Claves().count("aaaa") == 1);
    ASSERT_FALSE(vacio.Claves().count("adios") == 1);

    ASSERT_TRUE(sin_prefijos.Claves().count("hola") == 1);
    ASSERT_TRUE(sin_prefijos.Claves().count("chau") == 1);
    ASSERT_TRUE(sin_prefijos.Claves().count("adios") == 1);

    ASSERT_FALSE(sin_prefijos.Claves().count("ho") == 1);
    ASSERT_FALSE(sin_prefijos.Claves().count("h") == 1);
    ASSERT_FALSE(sin_prefijos.Claves().count("hol") == 1);

    ASSERT_TRUE(con_prefijos.Claves().count("c") == 1);
    ASSERT_TRUE(con_prefijos.Claves().count("casa") == 1);
    ASSERT_TRUE(con_prefijos.Claves().count("casona") == 1);
    ASSERT_FALSE(con_prefijos.Claves().count("ca") == 1);
    ASSERT_FALSE(con_prefijos.Claves().count("cas") == 1);
    ASSERT_FALSE(con_prefijos.Claves().count("caso") == 1);
}

TEST(string_map_test, copiar) {
    string_map<int> sin_prefijos;
    string_map<int> con_prefijos;

    sin_prefijos.Definir("hola", 1);
    sin_prefijos.Definir("chau", 2);
    sin_prefijos.Definir("adios",  3);

    con_prefijos.Definir("c",  1);
    con_prefijos.Definir("casa", 2);
    con_prefijos.Definir("casona", 3);

    string_map<int> copia(sin_prefijos);

    ASSERT_TRUE(copia.Definido("hola"));
    ASSERT_TRUE(copia.Definido("chau"));
    ASSERT_TRUE(copia.Definido("adios"));

    ASSERT_TRUE(copia.Claves().count("hola") == 1);
    ASSERT_TRUE(copia.Claves().count("chau") == 1);
    ASSERT_TRUE(copia.Claves().count("adios") == 1);

    ASSERT_FALSE(copia.Definido("h"));
    ASSERT_FALSE(copia.Definido("ho"));
    ASSERT_FALSE(copia.Definido("hol"));

    ASSERT_FALSE(copia.Claves().count("h") == 1);
    ASSERT_FALSE(copia.Claves().count("ho") == 1);
    ASSERT_FALSE(copia.Claves().count("hol") == 1);

    ASSERT_EQ(sin_prefijos.Significado("hola"), copia.Significado("hola"));
    ASSERT_EQ(sin_prefijos.Significado("chau"), copia.Significado("chau"));
    ASSERT_EQ(sin_prefijos.Significado("adios"), copia.Significado("adios"));

    string_map<int> copia2(con_prefijos);

    ASSERT_TRUE(copia2.Definido("c"));
    ASSERT_TRUE(copia2.Definido("casa"));
    ASSERT_TRUE(copia2.Definido("casona"));

    ASSERT_TRUE(copia2.Claves().count("c") == 1);
    ASSERT_TRUE(copia2.Claves().count("casa") == 1);
    ASSERT_TRUE(copia2.Claves().count("casona") == 1);

    ASSERT_FALSE(copia2.Definido("ca") == 1);
    ASSERT_FALSE(copia2.Definido("cas") == 1);
    ASSERT_FALSE(copia2.Definido("caso") == 1);

    ASSERT_FALSE(copia2.Claves().count("ca") == 1);
    ASSERT_FALSE(copia2.Claves().count("cas") == 1);
    ASSERT_FALSE(copia2.Claves().count("caso") == 1);

    ASSERT_EQ(copia2.Significado("c"), 1);
    ASSERT_EQ(copia2.Significado("casa"), 2);
    ASSERT_EQ(copia2.Significado("casona"), 3);
}

TEST(string_map_test, no_aliasing) {
    string_map<int> singleton;
    singleton.Definir("hola", 1);

    string_map<int> copia(singleton);
    copia.Definir("hare",  2);
    ASSERT_FALSE(singleton.Definido("hare"));
    ASSERT_FALSE(singleton.Claves().count("hare") == 1);
    ASSERT_FALSE(&singleton.Significado("hola") == &copia.Significado("hola"));
}

//TEST(string_map_test, TrieDeTries) {
//    string_map<int> vacio;
//    string_map<int> singleton;
//    string_map<int> sin_prefijos;
//    string_map<int> con_prefijos;
//    string_map<string_map<int>> dicc_dicc;
//
//    singleton["hola"] = 1;
//
//    sin_prefijos["hola"] = 1;
//    sin_prefijos["chau"] = 2;
//    sin_prefijos["adios"] =  3;
//
//    con_prefijos["c"] =  1;
//    con_prefijos["casa"] =  2;
//    con_prefijos["casona"] =  3;
//
//    dicc_dicc["vacio"] =  vacio;
//    dicc_dicc["singleton"] =  singleton;
//    dicc_dicc["sin_prefijos"] =  sin_prefijos;
//    dicc_dicc["con_prefijos"] =  con_prefijos;
//
//    ASSERT_FALSE(dicc_dicc["vacio"].count("hola") == 1);
//
//    ASSERT_EQ(dicc_dicc["singleton"]["hola"], 1);
//
//    ASSERT_EQ(dicc_dicc["sin_prefijos"]["hola"], 1);
//    ASSERT_EQ(dicc_dicc["sin_prefijos"]["chau"], 2);
//    ASSERT_EQ(dicc_dicc["sin_prefijos"]["adios"], 3);
//
//    ASSERT_EQ(dicc_dicc["con_prefijos"]["c"], 1);
//    ASSERT_EQ(dicc_dicc["con_prefijos"]["casa"], 2);
//    ASSERT_EQ(dicc_dicc["con_prefijos"]["casona"], 3);
//
//}
//
TEST(string_map_test, eraseUnicaClave) {
    string_map<int> singleton;
    singleton.Definir("hola", 1);

    ASSERT_TRUE(singleton.Definido("hola"));
    ASSERT_TRUE(singleton.Claves().count("hola") == 1);

    singleton.Borrar("hola");

    ASSERT_FALSE(singleton.Definido("hola"));
    ASSERT_FALSE(singleton.Claves().count("hola") == 1);
}


TEST(string_map_test, erase) {
    string_map<int> sin_prefijos;
    string_map<int> con_prefijos;

    sin_prefijos.Definir("hola", 1);
    sin_prefijos.Definir("chau", 2);
    sin_prefijos.Definir("adios",  3);

    con_prefijos.Definir("c",  1);
    con_prefijos.Definir("casa", 2);
    con_prefijos.Definir("casona", 3);

    con_prefijos.Borrar("c");
    ASSERT_FALSE(con_prefijos.Definido("c"));
    ASSERT_FALSE(con_prefijos.Claves().count("c") == 1);

    ASSERT_TRUE(con_prefijos.Definido("casa"));
    ASSERT_TRUE(con_prefijos.Claves().count("casa") == 1);
    ASSERT_TRUE(con_prefijos.Definido("casona"));
    ASSERT_TRUE(con_prefijos.Claves().count("casona") == 1);

    con_prefijos.Borrar("casona");
    ASSERT_FALSE(con_prefijos.Definido("casona"));
    ASSERT_FALSE(con_prefijos.Claves().count("casona") == 1);

    ASSERT_TRUE(con_prefijos.Definido("casa"));
    ASSERT_TRUE(con_prefijos.Claves().count("casa") == 1);

    con_prefijos.Borrar("casa");
    ASSERT_FALSE(con_prefijos.Definido("casa"));
    ASSERT_FALSE(con_prefijos.Claves().count("casa") == 1);

    sin_prefijos.Borrar("hola");
    ASSERT_FALSE(sin_prefijos.Definido("hola"));
    ASSERT_FALSE(sin_prefijos.Claves().count("hola") == 1);

    sin_prefijos.Borrar("chau");
    ASSERT_FALSE(sin_prefijos.Definido("chau"));
    ASSERT_FALSE(sin_prefijos.Claves().count("chau") == 1);

    sin_prefijos.Borrar("adios");
    ASSERT_FALSE(sin_prefijos.Definido("adios"));
    ASSERT_FALSE(sin_prefijos.Claves().count("adios") == 1);
}

TEST(string_map_test, no_aliasing_definiciones) {
    string_map<int> singleton;
    singleton.Definir("hola", 1);

    string_map<int> copia(singleton);

    singleton.Borrar("hola");

    ASSERT_TRUE(copia.Definido("hola"));
    ASSERT_TRUE(copia.Claves().count("hola") == 1);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
