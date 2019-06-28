#include "gtest-1.8.1/gtest.h"
#include "../src/modulos_basicos/string_map.h"

TEST(string_map_test, asignar) {
    string_map<int> singleton;
    singleton.Definir("hola", 1);

    ASSERT_EQ(singleton.Significado("hola"), 1);
    int a = singleton.Claves().count("hola");
    ASSERT_EQ(a, 1);
}

//TEST(string_map_test, obtener) {
//    string_map<int> sin_prefijos;
//    string_map<int> con_prefijos;
//
//    sin_prefijos["hola"] = 1;
//    sin_prefijos["chau"] = 2;
//    sin_prefijos["adios"] =  3;
//
//    con_prefijos["c"] =  1;
//    con_prefijos["casa"] =  2;
//    con_prefijos["casona"] =  3;
//
//    ASSERT_EQ(sin_prefijos["hola"], 1);
//    ASSERT_EQ(sin_prefijos["chau"], 2);
//    ASSERT_EQ(sin_prefijos["adios"], 3);
//
//    ASSERT_EQ(con_prefijos["c"], 1);
//    ASSERT_EQ(con_prefijos["casa"], 2);
//    ASSERT_EQ(con_prefijos["casona"], 3);
//}
//
//TEST(string_map_test, redefinir) {
//    string_map<int> con_prefijos;
//
//    con_prefijos["c"] =  1;
//    con_prefijos["casa"] =  2;
//    con_prefijos["casona"] =  3;
//
//    con_prefijos["c"] =  2;
//    ASSERT_EQ(con_prefijos["c"], 2);
//    con_prefijos["c"] =  3;
//    ASSERT_EQ(con_prefijos["c"], 3);
//}
//
//TEST(string_map_test, count) {
//    string_map<int> vacio;
//    string_map<int> sin_prefijos;
//    string_map<int> con_prefijos;
//
//    sin_prefijos["hola"] = 1;
//    sin_prefijos["chau"] = 2;
//    sin_prefijos["adios"] =  3;
//
//    con_prefijos["c"] =  1;
//    con_prefijos["casa"] =  2;
//    con_prefijos["casona"] =  3;
//
//    ASSERT_FALSE(vacio.count("a") == 1);
//    ASSERT_FALSE(vacio.count("aaaa") == 1);
//    ASSERT_FALSE(vacio.count("adios") == 1);
//
//    ASSERT_TRUE(sin_prefijos.count("hola") == 1);
//    ASSERT_TRUE(sin_prefijos.count("chau") == 1);
//    ASSERT_TRUE(sin_prefijos.count("adios") == 1);
//
//    ASSERT_FALSE(sin_prefijos.count("h") == 1);
//    ASSERT_FALSE(sin_prefijos.count("ho") == 1);
//    ASSERT_FALSE(sin_prefijos.count("hol") == 1);
//
//    ASSERT_TRUE(con_prefijos.count("c") == 1);
//    ASSERT_TRUE(con_prefijos.count("casa") == 1);
//    ASSERT_TRUE(con_prefijos.count("casona") == 1);
//    ASSERT_FALSE(con_prefijos.count("ca") == 1);
//    ASSERT_FALSE(con_prefijos.count("cas") == 1);
//    ASSERT_FALSE(con_prefijos.count("caso") == 1);
//}
//
//TEST(string_map_test, copiar) {
//    string_map<int> sin_prefijos;
//    string_map<int> con_prefijos;
//
//    sin_prefijos["hola"] = 1;
//    sin_prefijos["chau"] = 2;
//    sin_prefijos["adios"] =  3;
//
//    con_prefijos["c"] =  1;
//    con_prefijos["casa"] =  2;
//    con_prefijos["casona"] =  3;
//
//    string_map<int> copia(sin_prefijos);
//
//    ASSERT_TRUE(copia.count("hola") == 1);
//    ASSERT_TRUE(copia.count("chau") == 1);
//    ASSERT_TRUE(copia.count("adios") == 1);
//
//    ASSERT_FALSE(copia.count("h") == 1);
//    ASSERT_FALSE(copia.count("ho") == 1);
//    ASSERT_FALSE(copia.count("hol") == 1);
//
//    ASSERT_EQ(sin_prefijos["hola"], copia["hola"]);
//    ASSERT_EQ(sin_prefijos["chau"], copia["chau"]);
//    ASSERT_EQ(sin_prefijos["adios"], copia["adios"]);
//
//    string_map<int> copia2(con_prefijos);
//
//    ASSERT_TRUE(copia2.count("c") == 1);
//    ASSERT_TRUE(copia2.count("casa") == 1);
//    ASSERT_TRUE(copia2.count("casona") == 1);
//    ASSERT_FALSE(copia2.count("ca") == 1);
//    ASSERT_FALSE(copia2.count("cas") == 1);
//    ASSERT_FALSE(copia2.count("caso") == 1);
//
//    ASSERT_EQ(copia2["c"], 1);
//    ASSERT_EQ(copia2["casa"], 2);
//    ASSERT_EQ(copia2["casona"], 3);
//}
//
//TEST(string_map_test, no_aliasing) {
//    string_map<int> singleton;
//    singleton["hola"] = 1;
//
//    string_map<int> copia(singleton);
//    copia["hare"] =  2;
//    ASSERT_FALSE(singleton.count("hare") == 1);
//}
//
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
//TEST(string_map_test, eraseUnicaClave) {
//    string_map<int> singleton;
//    singleton["hola"] = 1;
//
//    ASSERT_TRUE(singleton.count("hola") == 1);
//
//    singleton.erase("hola");
//
//    ASSERT_FALSE(singleton.count("hola") == 1);
//}
//
//
//TEST(string_map_test, erase) {
//    string_map<int> sin_prefijos;
//    string_map<int> con_prefijos;
//
//    sin_prefijos["hola"] = 1;
//    sin_prefijos["chau"] = 2;
//    sin_prefijos["adios"] =  3;
//
//    con_prefijos["c"] =  1;
//    con_prefijos["casa"] =  2;
//    con_prefijos["casona"] =  3;
//
//    con_prefijos.erase("c");
//    ASSERT_FALSE(con_prefijos.count("c") == 1);
//
//    ASSERT_TRUE(con_prefijos.count("casa") == 1);
//    ASSERT_TRUE(con_prefijos.count("casona") == 1);
//
//    con_prefijos.erase("casona");
//    ASSERT_FALSE(con_prefijos.count("casona") == 1);
//
//    ASSERT_TRUE(con_prefijos.count("casa") == 1);
//
//    con_prefijos.erase("casa");
//    ASSERT_FALSE(con_prefijos.count("casa") == 1);
//
//    sin_prefijos.erase("hola");
//    ASSERT_FALSE(sin_prefijos.count("hola") == 1);
//
//    sin_prefijos.erase("chau");
//    ASSERT_FALSE(sin_prefijos.count("chau") == 1);
//
//    sin_prefijos.erase("adios");
//    ASSERT_FALSE(sin_prefijos.count("adios") == 1);
//}
//
//TEST(string_map_test, no_aliasing_definiciones) {
//    string_map<int> singleton;
//    singleton["hola"] = 1;
//
//    string_map<int> copia(singleton);
//
//    singleton.erase("hola");
//
//    ASSERT_TRUE(copia.count("hola") == 1);
//}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
