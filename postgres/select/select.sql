


-------------------
-- V
-- Вывести товары которые никогда не покупались
-- теми покупателями которые покупали мак. кол-во товаров
-------------------



SELECT name
FROM products
LEFT JOIN order_position ON order_position.product_id = products.id
LEFT JOIN orders ON orders.id = order_position.order_id AND orders.customer_id = (
        SELECT orders.customer_id
            -- , count(order_position.product_id) AS count_products
     FROM order_position
     JOIN orders ON orders.id = order_position.order_id
     GROUP BY order_position.product_id, orders.customer_id
     ORDER BY count(order_position.product_id) DESC
     LIMIT 1
)
WHERE order_position.product_id IS NULL;

Убрать limit


-------------------
-- VI
-- Вывести заказы с самым долгим периодом оплаты
-- по кол-ву дней в простое
-------------------


SELECT id, datetime_payment, datetime_registration, (datetime_payment - datetime_registration) AS diff
FROM orders
ORDER BY (datetime_payment - datetime_registration) desc nulls last;



-------------------
-- III
-- Рейтинг товаров которые популярны среди физ. и юр. лиц
-- 1) Сортировка по кол-ву купленных товаров
-- 2) Пересечение по продуктов физ и юр лиц
-------------------


-- explain analyze

SELECT name,
       sum(order_position.count_products) AS sum_products
FROM products
JOIN order_position ON order_position.product_id = products.id
WHERE id IN (
        SELECT order_position.product_id
        FROM order_position
        JOIN orders ON orders.id = order_position.order_id
        JOIN person_entity AS person ON person.customer_id = orders.customer_id
        WHERE orders.is_cancel IS FALSE
        GROUP BY order_position.product_id
        INTERSECT
        SELECT order_position.product_id
        FROM order_position
        JOIN orders ON orders.id = order_position.order_id
        JOIN legal_entity AS legal ON legal.customer_id = orders.customer_id
        WHERE orders.is_cancel IS FALSE
        GROUP BY order_position.product_id
)
GROUP BY products.name
ORDER BY sum(order_position.count_products) DESC;


-- /*
-------------------
-- II
-- Вывести рейтинг покупателей (отдельно физ и юр лиц) (в два столбца)
-- 1) по сумме оплаченных товаров
-- 2) по мин. кол-ву оповещений среди которых есть оплаченные
-------------------


-- 1) убрать отмененные заказы
-- 2) сумма по оплаченным квитанциям
-- 3) 



select
    orders.customer_id,
    sum(orders.cost),
    COALESCE(legal.company_name, person.last_name || ' ' || person.first_name || ' ' || person.middle_name, 'unknown') AS name
from orders
left JOIN legal_entity AS legal ON legal.customer_id = orders.customer_id
left JOIN person_entity AS person ON person.customer_id = orders.customer_id
JOIN order_position ON order_position.order_id = orders.id
group by orders.customer_id, name
order by sum(orders.cost) desc, orders.customer_id = (
    select orders.customer_id
    from orders
    join notify on notify.order_id = orders.id
    where orders.is_cancel is false and notify.is_paid is true
    group by orders.id
    having count(*) <= 1
    order by count(*)
    limit 1
) desc


Убрать limit


-------------------
-- I
-- Вывести номер заказа, наименование клиента, стоимость заказа
-- где кол-во оповещений было больше 2
-------------------

-- explain analyze

SELECT orders.id,
       COALESCE(legal.company_name, person.last_name || ' ' || person.first_name || ' ' || person.middle_name, 'unknown') AS name,
       orders.cost
FROM orders
JOIN customers ON customers.id = orders.customer_id
LEFT JOIN person_entity AS person ON person.customer_id = orders.customer_id
LEFT JOIN legal_entity AS legal ON legal.customer_id = orders.customer_id
WHERE orders.id IN
        ( SELECT orders.id
         FROM orders
         JOIN notify ON notify.order_id = orders.id
         GROUP BY orders.id
         HAVING count(notify.id) > 1)
GROUP BY orders.id, name
