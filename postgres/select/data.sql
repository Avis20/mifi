

truncate "products" cascade; ALTER SEQUENCE products_id_seq RESTART;
truncate "customers" cascade; ALTER SEQUENCE customers_id_seq RESTART;
truncate "orders" cascade; ALTER SEQUENCE orders_id_seq RESTART;
truncate "quittances" cascade; ALTER SEQUENCE quittances_id_seq RESTART;
truncate "notify" cascade; ALTER SEQUENCE notify_id_seq RESTART;

-- Создаем 3 покупателей

-- физ. лицо 1
INSERT INTO "customers" (date_registration) VALUES ('2019-10-19');
INSERT INTO "person_entity" (customer_id, last_name, first_name, middle_name, date_birth, passport_data, address, phone)
VALUES (lastval(), 'Yermolayev', 'Eric', 'Saveliev', '1996-10-12', '8202231098', 'Woodlawn Drive New Berlin, WI 53151', '414-558-5587');

-- физ. лицо 2
INSERT INTO "customers" (date_registration) VALUES ('2019-10-19');
INSERT INTO "person_entity" (customer_id, last_name, first_name, middle_name, date_birth, passport_data, address, phone)
VALUES (lastval(), 'Morris', 'James', 'Saveliev', '1986-11-16', '894894896', '4721 Masonic Drive Terry, MT 59349', '489-189-7894');

-- юр. лицо 1
INSERT INTO "customers" (date_registration) VALUES ('2019-11-17');
insert into "legal_entity" ( customer_id, company_name, address, phone, license_number, bank_details, company_category )
values (lastval(), 'Baker', '922 Glen Street Bowling Green, KY 42101', '270-392-2311','403-66-XXXX', 'Prahject Planner', 'Business');

---------------------
-- Товары 
---------------------

-- На складе 100 тетрадей и 50 ручек и 500 ластиков
INSERT INTO "products" (name, article, number_quality_certificate, package, manufacturer_name, count_in_storage, selling_price)
VALUES ('тетрадь', '12b14', 1234, 'коробка', 'альфа', 100, 5);
INSERT INTO "products" (name, article, number_quality_certificate, package, manufacturer_name, count_in_storage, selling_price)
VALUES ('ручка', '22b14', 1334, 'коробка', 'бета', 50, 2);
INSERT INTO "products" (name, article, number_quality_certificate, package, manufacturer_name, count_in_storage, selling_price)
VALUES ('ластик', 'у2121у21', 47328947, 'коробка', 'гамма', 500, 1);

INSERT INTO "products" (name, article, number_quality_certificate, package, manufacturer_name, count_in_storage, selling_price)
VALUES ('файл2', 'ааа', 32132, 'коробка', 'гамма', 500, 1);


---------------------
-- Заказы 1-го покупателя
---------------------

-- Заказ 1-го покупателя - 20 тетрадей по 5 руб. на 100 руб.
-- 2 платежа на 40 и 60 руб. + для каждой платежки - нотификация
INSERT INTO "orders" (customer_id, count_products, cost, is_cancel, datetime_registration)
VALUES (1, 20, 100, FALSE, '2019-11-01'); -- order=1
INSERT INTO "order_position" (order_id, product_id, count_products) VALUES (1, 1, 20);

-- Платеж на 40 руб.
INSERT INTO "quittances" (order_id, type, payment_amount) VALUES (1, 'платеж', 40); -- quittance=1
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid) VALUES (1, 1, 1, TRUE); -- notify=1

-- Платеж на 60 руб.
INSERT INTO "quittances" (order_id, type, payment_amount) VALUES (1, 'платеж', 60); -- quittance=2
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid) VALUES (1, 1, 2, TRUE); -- notify=2

UPDATE "orders" set datetime_payment = '2019-11-02' where id = 1;

-- Заказ 1-го покупателя - 10 тетрадей по 5 руб. на 50 руб.
INSERT INTO "orders" (customer_id, count_products, cost, is_cancel, datetime_registration)
VALUES (1, 10, 50, FALSE, '2019-11-01'); -- order=2
INSERT INTO "order_position" (order_id, product_id, count_products) VALUES (2, 1, 10);

-- Платеж на 50 руб.
INSERT INTO "quittances" (order_id, type, payment_amount) VALUES (2, 'платеж', 50); -- quittance=3
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid) VALUES (1, 2, 3, TRUE); -- notify=3

UPDATE "orders" set datetime_payment = '2019-11-03' where id = 2;

---------------------
-- Заказы 3-го покупателя
---------------------

-- Заказ 3-го покупателя - 3 тетради по 5 руб. на 15 руб.
INSERT INTO "orders" (customer_id, count_products, cost, is_cancel) VALUES (3, 3, 15, FALSE); -- order=3
INSERT INTO "order_position" (order_id, product_id, count_products) VALUES (3, 1, 15);

-- Платеж на 15 руб.
INSERT INTO "quittances" (order_id, type, payment_amount) VALUES (3, 'платеж', 15); -- quittance=4
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid) VALUES (3, 3, 4, TRUE); -- notify=4

-- Отмена 
update "orders" set is_cancel = true where id = 3; -- quittance=5, notify=5

-- Заказ 3-го покупателя
-- 40 ручек по 2 руб. на 80 руб.
-- 20 тетрадей по 5 руб. на 100 руб.
INSERT INTO "orders" (customer_id, count_products, cost, is_cancel) VALUES (3, 60, 180, FALSE); -- order=4
INSERT INTO "order_position" (order_id, product_id, count_products) VALUES (4, 2, 40);
INSERT INTO "order_position" (order_id, product_id, count_products) VALUES (4, 1, 20);

-- Платеж на 150 руб.
-- Долг 30 руб.
INSERT INTO "quittances" (order_id, type, payment_amount) VALUES (4, 'платеж', 150); -- quittance=6
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid) VALUES (3, 4, 6, TRUE); -- notify=6

-- Оповещение о долге 1
INSERT INTO "notify" (customer_id, order_id, is_paid) VALUES (3, 4, FALSE); -- notify=7

-- Оповещение о долге 2
INSERT INTO "notify" (customer_id, order_id, is_paid) VALUES (3, 4, FALSE); -- notify=8

-- Оплата долга + update оповещения
INSERT INTO "quittances" (order_id, type, payment_amount) VALUES (4, 'платеж', 30); -- quittance=7 
-- ????? update "notify" set quittance_id = lastval() where customer_id = 3 AND order_id = 4;
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid) VALUES (3, 4, 7, TRUE); -- notify=9

-- Заказ 3-го покупателя - 20 тетради по 5 руб. на 100 руб.
-- ЗАКАЗ КОТОРЫЙ ЕЩЕ НЕ ОПЛАЧЕН
INSERT INTO "orders" (customer_id, count_products, cost, is_cancel) VALUES (3, 20, 100, FALSE); -- order=5
INSERT INTO "order_position" (order_id, product_id, count_products) VALUES (5, 1, 20);

INSERT INTO "notify" (customer_id, order_id, is_paid) VALUES (3, 5, FALSE); -- notify=10


---------------------
-- Заказы 2-го покупателя
---------------------

-- Заказ 2-го покупателя - 30 тетрадей по 5 руб. на 180 руб.
INSERT INTO "orders" (customer_id, count_products, cost, is_cancel) VALUES (2, 30, 180, FALSE); -- order=6
INSERT INTO "order_position" (order_id, product_id, count_products) VALUES (6, 1, 30);

-- Платеж на 180 руб.
INSERT INTO "quittances" (order_id, type, payment_amount) VALUES (6, 'платеж', 180); -- quittance=8
INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid) VALUES (2, 6, 8, TRUE); -- notify=11


-- Заказ 3-го покупателя - 10 ластиков по 1 руб. на 10 руб.
INSERT INTO "orders" (customer_id, count_products, cost, is_cancel) VALUES (3, 10, 10, FALSE); -- order=7
INSERT INTO "order_position" (order_id, product_id, count_products) VALUES (7, 3, 10);


-- Заказ 2-го покупателя - 20 ластиков по 1 руб. на 20 руб.
INSERT INTO "orders" (customer_id, count_products, cost, is_cancel, datetime_registration)
VALUES (2, 20, 20, FALSE, '2019-11-05'); -- order=8
INSERT INTO "order_position" (order_id, product_id, count_products) VALUES (8, 2, 20);

UPDATE "orders" set datetime_payment = '2019-11-10' where id = 8;

-- Заказ 1-го покупателя - 25 ручек по 2 руб. на 50 руб.
INSERT INTO "orders" (customer_id, count_products, cost, is_cancel, datetime_registration)
VALUES (1, 25, 50, FALSE, '2019-11-05'); -- order=9
INSERT INTO "order_position" (order_id, product_id, count_products) VALUES (9, 2, 25);


/*

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

*/