# project2_HDH
- [Bài 1. Đồng bộ giữa các tiểu trình ](#bài-1-đồng-bộ-giữa-các-tiểu-trình)
- [Bài 2.  Đồng bộ giữa các tiểu trình và tiến trình](#bài-2-đồng-bộ-giữa-các-tiểu-trình-và-tiến-trình)

   - [2.1 Đông bộ các tiểu trình]()
   - [2.2 Đông bộ các tiến trình]()
- [Bài 3. Đồng bộ số lượng giữa các tiểu trình ](#bài-3-đồng-bộ-số-lượng-giữa-các-tiểu-trình)
- [Tham khảo](#tham-khảo) 
 
   - [Thread in C](https://www.geeksforgeeks.org/thread-functions-in-c-c/)
   - [Mulitithread in C](https://www.geeksforgeeks.org/multithreading-c-2/)
   - [Semaphore in C](https://www.geeksforgeeks.org/use-posix-semaphores-c/)


## Bài 1 Đồng bộ giữa các tiểu trình
sem_t mutex: đồng bộ `Độc quyền truy xuất ` với value = 1
## Bài 2 Đồng bộ giữa các tiểu trình và tiến trình
sem_t *sem1, *sem2: đồng bộ `Độc quyền truy xuất` giữa 2 tiểu trình
```
*sem1: sau khi A1 chạy xong --> A1 sẽ up (value) --> B2 lúc này mới chạy 
*sem2: sau khi B1 chạy xong --> B1 sẽ up (value) --> A2 lúc này mới được chạy
```
## Bài 3 Đồng bộ số lượng giữa các tiểu trình
Trong bài này sẽ có 5 sem
sem_t sem1, sem2, sem3, sem4 và sem_t mutex

```
sem1: điều phối hẹn hò giữa  2H -> 1H20 --> Sau khi 2 H chạy thì H20 mới được chạy
sem2: điều phối hẹn hò giữa  1O -> 1H20 --> Sau khi O chạy thì H20 mới được chạy
sem3: điều phối hẹn hò giữa  1H20 -> 1O --> sau khi H20 chạy thì O mới được chạy ( Trong lần đầu chạy thì O không phải đợi vì value initial = 1 )
sem4: điều phối hẹn hò giữa  1H20 -> 2H --> sau khi H20 chạy thì 2H mới được chạy ( Trong lần đầu chạy thì H không phải đợi vì value initial = 2 )
mutex: điều phối truy xuất độc quyền giữa các thread H2O 
```
## Tham khảo
https://www.geeksforgeeks.org/thread-functions-in-c-c/


https://www.geeksforgeeks.org/multithreading-c-2/


https://www.geeksforgeeks.org/use-posix-semaphores-c/
