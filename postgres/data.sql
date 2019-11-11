

---------------------
-- 0) подготовка данных
---------------------

truncate "products" cascade; ALTER SEQUENCE products_id_seq RESTART;
truncate "customers" cascade; ALTER SEQUENCE customers_id_seq RESTART;
truncate "quittances" cascade; ALTER SEQUENCE quittances_id_seq RESTART;
truncate "notify" cascade; ALTER SEQUENCE notify_id_seq RESTART;
-- truncate "waybills" cascade; ALTER SEQUENCE waybills_id_seq RESTART;

-- На складе 100 тетрадей и 50 ручек
INSERT INTO "products" (id, name, article, number_quality_certificate, PACKAGE, manufacturer_name, count_in_storage, selling_price)
VALUES (1, 'тетрадь', '12b14', 1234, 'коробка', 'альфа', 100, 5);
INSERT INTO "products" (id, name, article, number_quality_certificate, PACKAGE, manufacturer_name, count_in_storage, selling_price)
VALUES (2, 'ручка', '22b14', 1334, 'коробка', 'бета', 50, 2);

-- Создаем 2 покупателя
INSERT INTO "customers" (id, date_registration) VALUES (1, '2019-10-19');
INSERT INTO "person_entity" (customer_id, last_name, first_name, middle_name, date_birth, passport_data, address, phone)
VALUES (1, 'Yermolayev', 'Eric', 'Saveliev', '1996-10-12', '8202231098', 'Woodlawn Drive New Berlin, WI 53151', '414-558-5587');

INSERT INTO "customers" (id, date_registration) VALUES (2, '2019-10-19');
INSERT INTO "person_entity" (customer_id, last_name, first_name, middle_name, date_birth, passport_data, address, phone)
VALUES (2, 'Morris', 'James', 'Saveliev', '1986-11-16', '894894896', '4721 Masonic Drive Terry, MT 59349', '489-189-7894');

---------------------
-- Заказы 1-го покупателя
---------------------

-- Заказ 1-го покупателя - 20 тетрадей по 5 руб. на 100 руб.
-- 2 платежа на 40 и 60 руб. + для каждой платежки - нотификация
INSERT INTO "orders" (id, customer_id, count_products, cost, is_cancel)
VALUES (1, 1, 20, 100, FALSE);
INSERT INTO "order_position" (order_id, product_id, count_products)
VALUES (1, 1, 20);

-- Платеж на 40 руб.
INSERT INTO "quittances" (order_id, type, payment_amount)
VALUES (1, 'платеж', 40);
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid)
VALUES (1, 1, 1, FALSE);

-- Платеж на 60 руб.
INSERT INTO "quittances" (order_id, type, payment_amount)
VALUES (1, 'платеж', 60);
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid)
VALUES (1, 1, 2, FALSE);


-- Заказ 1-го покупателя - 10 тетрадей по 5 руб. на 50 руб.
INSERT INTO "orders" (id, customer_id, count_products, cost, is_cancel)
VALUES (2, 1, 10, 50, FALSE);
INSERT INTO "order_position" (order_id, product_id, count_products)
VALUES (2, 1, 10);

-- Платеж на 50 руб.
INSERT INTO "quittances" (order_id, type, payment_amount)
VALUES (2, 'платеж', 50);
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid)
VALUES (1, 2, 3, FALSE);


-- Заказ 1-го покупателя - 20 ручек по 2 руб. на 40 руб.
INSERT INTO "orders" (id, customer_id, count_products, cost, is_cancel)
VALUES (3, 1, 20, 40, FALSE);
INSERT INTO "order_position" (order_id, product_id, count_products)
VALUES (3, 2, 20);

-- Платеж на 40 руб.
INSERT INTO "quittances" (order_id, type, payment_amount)
VALUES (3, 'платеж', 40);
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid)
VALUES (1, 3, 4, FALSE);

---------------------
-- Заказы 2-го покупателя
---------------------

-- Заказ 2-го покупателя - 40 тетрадей по 5 руб. на 200 руб.
INSERT INTO "orders" (id, customer_id, count_products, cost, is_cancel)
VALUES (4, 2, 40, 200, FALSE);
INSERT INTO "order_position" (order_id, product_id, count_products)
VALUES (4, 1, 40);

-- Платеж на 200 руб.
INSERT INTO "quittances" (order_id, type, payment_amount)
VALUES (4, 'платеж', 200);
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid)
VALUES (2, 4, 5, FALSE);

-- Заказ 2-го покупателя - 10 ручек по 2 руб. на 20 руб.
INSERT INTO "orders" (id, customer_id, count_products, cost, is_cancel)
VALUES (5, 2, 10, 20, FALSE);
INSERT INTO "order_position" (order_id, product_id, count_products)
VALUES (5, 2, 10);

-- Платеж на 20 руб.
INSERT INTO "quittances" (order_id, type, payment_amount)
VALUES (5, 'платеж', 20);
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid)
VALUES (2, 5, 6, FALSE);

-- отмена платежа 2-го покупателей

update "orders" set is_cancel = true where id = 4;
update "orders" set is_cancel = true where id = 5;




------------------
-- 1) анализ отмены
-- на вход - ном товара
-- если отмен во всех заказах > половины, то в товаре ставиться флаг = брак
------------------

select product_cancel_analysis(1);


select product_cancel_analysis(2);


select * from "public"."products";


------------------
-- 2) авто оповещения
-- на вход дата заказа
-- если все данные есть то генерировать оповещение на основе всех данных 
------------------


-- Заказ 1-го покупателя - 3 ручки по 2 руб. на 6 руб.
INSERT INTO "orders" (id, customer_id, count_products, cost, is_cancel)
VALUES (6, 1, 3, 6, FALSE);

-- Заказ 2-го покупателя - 5 ручек по 2 руб. на 10 руб.
INSERT INTO "orders" (id, customer_id, count_products, cost, is_cancel)
VALUES (7, 2, 5, 10, FALSE);

INSERT INTO "quittances" (order_id, type, payment_amount)
VALUES (6, 'платеж', 6);


select auto_notify('2019-11-03');



/*
    Триггер #1


truncate "products" cascade;
truncate "waybills" cascade;

ALTER SEQUENCE products_id_seq RESTART;
ALTER SEQUENCE waybills_id_seq RESTART;

-- На складе 100 тетрадей и 30 ручек
INSERT INTO "products" (id, name, article, number_quality_certificate, PACKAGE, manufacturer_name, count_in_storage, selling_price)
VALUES (1, 'тетрадь', '12b14', 1234, 'коробка', 'альфа', 100, 5);

INSERT INTO "products" (id, name, article, number_quality_certificate, PACKAGE, manufacturer_name, count_in_storage, selling_price)
VALUES (2, 'ручка', '22b14', 1334, 'коробка', 'бета', 30, 2);

-- Накладная на 20 товаров, 10 ручек и 10 тетрадей
INSERT INTO "waybills" (id, date_receipt, total_product, total_cost) VALUES (1, '2019-10-18', 20, 100) RETURNING id;

select * from "products";
select * from "waybills";
select * from "deliveries";

INSERT INTO "deliveries" (waybill_id, product_id, count_products) VALUES (1, 1, 10);
INSERT INTO "deliveries" (waybill_id, product_id, count_products) VALUES (1, 2, 10);

select * from "products";


/*
    Триггер #2


TRUNCATE "customers" CASCADE;
TRUNCATE "products" CASCADE;
ALTER SEQUENCE quittances_id_seq RESTART;
ALTER SEQUENCE notify_id_seq RESTART;

-- Создаем покупателя
INSERT INTO "customers" (id, date_registration) VALUES (1, '2019-10-19');

INSERT INTO "person_entity" (customer_id, last_name, first_name, middle_name, date_birth, passport_data, address, phone)
VALUES (1, 'Yermolayev', 'Eric', 'Saveliev', '1996-10-12', '8202231098', 'Woodlawn Drive New Berlin, WI 53151', '414-558-5587');

SELECT * FROM "person_entity";

-- Создаем товар
INSERT INTO products (id, name, article, number_quality_certificate, PACKAGE, manufacturer_name, count_in_storage, selling_price)
VALUES (3, 'карандаш', '47489', 486, 'шт', 'wdfq8', 100, 5);

-- Заказ, документ об оплате, оповещение
INSERT INTO "orders" (id, customer_id, count_products, cost, is_cancel)
VALUES (1, 1, 20, 100, FALSE);

INSERT INTO "order_position" (order_id, product_id, count_products)
VALUES (1, 3, 20);

select * from "orders";

-- Платеж на 40 руб.
INSERT INTO "quittances" (order_id, type, payment_amount)
VALUES (1, 'платеж', 40);
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid)
VALUES (1, 1, 4, FALSE);

-- Платеж на 60 руб.
INSERT INTO "quittances" (order_id, type, payment_amount)
VALUES (1, 'платеж', 60);
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid)
VALUES (1, 1, 5, FALSE);

select 'ДО ОТМЕНЫ ЗАКАЗА';
SELECT * FROM "person_entity";
SELECT * FROM "orders";
SELECT * FROM "order_position";
SELECT * FROM "quittances";
SELECT * FROM "notify";

update "orders" set is_cancel = true where id = 1;

select 'ПОСЛЕ ОТМЕНЫ ЗАКАЗА';
SELECT * FROM "orders";
SELECT * FROM "quittances";
SELECT * FROM "notify";

