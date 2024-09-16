# LFU_cache
Реализация алгоритма LFU (Least frequency used) на C++ и его сравнение с идеальным кэшированием.  
Скачать репозиторий:  
```git clone https://github.com/kakov1/LFU_cache.git ```  
Сборка проекта:
```
cd LFU_cache/Cache/
cmake -S . -B build
cd build/
make
```  
Запуск LFU кэша:  
```
./cache
```  
Запуск идеального кэша:  
```
./ideal_cache
```  
Запуск тестов и сравнения с идеальным кэшированием (из основной папки):  
```
cd Tests/
./start_tests
```