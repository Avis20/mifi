#include <stdio.h>
#include <malloc.h>

typedef struct Node {   // Узел
    int data;           // Само значение
    struct Node *next;  // Указатель на следующий элемент
} Node;

typedef struct queue {  // Очередь
    Node *head;         // Вершина очереди
    Node *tail;         // Хвост
} Queue;

int put(Queue *, int);
int get(Queue *, int *);

int init(Queue *, int *, int);
void print(Queue *);

int main(){

    Queue queue = {NULL, NULL};
    int Q[] = {12, 23, 38, 43, 58};
    int size = sizeof(Q) / sizeof(Q[0]);
    init(&queue, Q, size);

    int pb = 5, pe = 3; // Что это? Oo

    printf("AFTER INIT\n");
    print(&queue);
    printf("\n");

    printf("AFTER GET\n");
    int el;
    get(&queue, &el);
    printf("el = %d\n", el);
    print(&queue);
    printf("\n");

    printf("AFTER PUT\n");
    put(&queue, 3);
    put(&queue, 13);
    print(&queue);
    printf("\n");

    return 0;
}

// Извлечение элемента из очереди
int get(Queue *queue, int *pel){
   
   // Вспомогательная переменная, в начале принимает значение вершины
   Node *node = queue->head;
 
   // Если список не пуст
   if (node){
      
      // Если в списке всего один элемент
      if (queue->head == queue->tail){
         queue->head = queue->tail = NULL;
      } else{
         
         // указатель на голову смещаем ниже на один узел
         queue->head = node->next;
         
         // Хвост должен указывать на новый верхний узел
         queue->tail->next = queue->head;
      }
 
      // Удаляем отделённый узел
      free(node);
   }
 
   return queue;
}

/
    // Пока есть элементы в очереди
    if (queue->head){
        // Сохраняем указатель на удаляемый элемент
        node = queue->head;

        // Сохраняем значение удаляемого элемента
        *pel = node->data;

        // Вершиной очереди становится следующий за удаляемым элемент
        queue->head = queue->head->next;

        // Окончательно удаляем элемент
        free(node);
    }
 
    return 1;
}

void print(Queue *queue){
    Node *node = queue->head;
    
    printf("HEAD = %d; TAIL = %d\nQueue: ", queue->head->data, queue->tail->data);

    do {
        printf("%d, ", node->data);
    } while ( ( node = node->next ) != NULL );

    printf("\n");
}

int init(Queue *queue, int *arr, int size){
    for (int i = 0; i < size; i++){
        put(queue, arr[i]);
    };
}

int put(Queue *queue, int el){

    // Создание нового узла
    Node *node = malloc(sizeof(Node));

    // Присваиваем значение новому узлу
    node->data = el;

    // Т.к. элемент добавляется в хвост, то указатель на следующий элемент ни на что не ссылается
    node->next = NULL;

    // Если очередь не пуста, то
    if (queue->head && queue->tail){
        
        // Хвостовой элемент ссылается на созданный узел
        queue->tail->next = node;
        // Созданный узел становится хвостом
        queue->tail = node;
    } else {
        // Первый элемент, теперь он и вершина и хвост
        queue->head = queue->tail = node;
    }

    return 1;
}
