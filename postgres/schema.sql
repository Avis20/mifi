

-- Покупатель (customer):

CREATE TABLE public.customers (
  id SERIAL,
  date_registration DATE DEFAULT now() NOT NULL,
  PRIMARY KEY(id)
);

COMMENT ON COLUMN public.customers.id IS 'ID покупателя';
COMMENT ON COLUMN public.customers.date_registration IS 'дата регистрации';

-- Юр. лицо (legal):

CREATE TABLE public.legal_entity (
  customer_id INTEGER REFERENCES public.customers(id) NOT NULL,
  company_name VARCHAR(100) not null unique,
  address VARCHAR(100),
  phone VARCHAR(20),
  license_number VARCHAR(50),
  bank_details VARCHAR(200),
  company_category VARCHAR(50),
  PRIMARY KEY(customer_id)
);

COMMENT ON COLUMN public.legal_entity.customer_id IS 'ID покупателя';
COMMENT ON COLUMN public.legal_entity.company_name IS 'название фирмы';
COMMENT ON COLUMN public.legal_entity.address IS 'адрес';
COMMENT ON COLUMN public.legal_entity.phone IS 'телефон';
COMMENT ON COLUMN public.legal_entity.license_number IS 'номер лицезии';
COMMENT ON COLUMN public.legal_entity.bank_details IS 'банковские реквизиты';
COMMENT ON COLUMN public.legal_entity.company_category IS 'категория фирмы';

-- Физ. лицо (person):

CREATE TABLE public.person_entity (
  customer_id INTEGER REFERENCES public.customers(id) NOT NULL,
  last_name VARCHAR(100),
  first_name VARCHAR(100),
  middle_name VARCHAR(100),
  date_birth DATE,
  passport_data VARCHAR(100) unique,
  address VARCHAR(100),
  phone VARCHAR(100),
  email VARCHAR(30),
  PRIMARY KEY(customer_id)
);

COMMENT ON COLUMN public.person_entity.customer_id IS 'ID покупателя';
COMMENT ON COLUMN public.person_entity.last_name IS 'фамилия';
COMMENT ON COLUMN public.person_entity.first_name IS 'имя';
COMMENT ON COLUMN public.person_entity.middle_name IS 'отчетсво';
COMMENT ON COLUMN public.person_entity.date_birth IS 'год рождения';
COMMENT ON COLUMN public.person_entity.passport_data IS 'паспортные данные';
COMMENT ON COLUMN public.person_entity.address IS 'адрес';
COMMENT ON COLUMN public.person_entity.phone IS 'телефон';
COMMENT ON COLUMN public.person_entity.email IS 'email';

-- ##################################################
-- ##################################################
-- ##################################################

-- Товар (product):

-- drop table "products" cascade;

CREATE TABLE public."products" (
  id SERIAL,
  name VARCHAR(100) NOT NULL,
  article VARCHAR(100),
  number_quality_certificate VARCHAR(100),
  package VARCHAR(100),
  manufacturer_name VARCHAR(100),
  count_in_storage INTEGER DEFAULT 0 NOT NULL CHECK (count_in_storage > 0),
  selling_price NUMERIC CHECK (selling_price > 0),
  is_defect BOOLEAN DEFAULT FALSE,
  PRIMARY KEY(id)
);

COMMENT ON COLUMN public.products.id IS 'ID товара';
COMMENT ON COLUMN public.products.name IS 'наименование товара';
COMMENT ON COLUMN public.products.article IS 'артикул';
COMMENT ON COLUMN public.products.number_quality_certificate IS 'номер сертификата качества';
COMMENT ON COLUMN public.products.package IS 'упаковка';
COMMENT ON COLUMN public.products.manufacturer_name IS 'название фирмы производителя';
COMMENT ON COLUMN public.products.count_in_storage IS 'Кол-во на складе';
COMMENT ON COLUMN public.products.selling_price IS 'Отпускная цена';
COMMENT ON COLUMN public.products.is_defect IS 'Брак';

-- Заказ (order):

-- drop table "orders" RESTRICT;

CREATE TABLE public."orders" (
  id SERIAL,
  customer_id INTEGER REFERENCES public.customers(id) NOT NULL,
  datetime_registration TIMESTAMP(0) WITHOUT TIME ZONE DEFAULT now() NOT NULL,
  datetime_first_notify TIMESTAMP(0) WITHOUT TIME ZONE,
  datetime_payment TIMESTAMP(0) WITHOUT TIME ZONE,
  datetime_product_end TIMESTAMP(0) WITHOUT TIME ZONE,
  count_products INTEGER DEFAULT 0 NOT NULL CHECK (count_products > 0),
  payment_status VARCHAR(100),
  cost NUMERIC CHECK (cost > 0),
  is_cancel boolean not null default false,
  PRIMARY KEY(id)
);

COMMENT ON COLUMN public."orders".id IS 'ID заказа';
COMMENT ON COLUMN public."orders".customer_id IS 'ID покупателя';
COMMENT ON COLUMN public."orders".datetime_registration IS 'дата и время оформления';
COMMENT ON COLUMN public."orders".datetime_payment IS 'дата и время оплаты';
COMMENT ON COLUMN public."orders".datetime_first_notify IS 'дата отправки первого оповещения';
COMMENT ON COLUMN public."orders".datetime_product_end IS 'крайний срок отпуска товара со склада';
COMMENT ON COLUMN public."orders".count_products IS 'кол-во товаров';
COMMENT ON COLUMN public."orders".payment_status IS 'отметка о продаже(отмене) покупки товара';
COMMENT ON COLUMN public."orders".cost IS 'стоимость покупки';

CREATE OR REPLACE FUNCTION orders_update_is_cancel_after_tr ()
RETURNS trigger AS
$body$
DECLARE
  total_amount numeric;
  new_quittance_id integer;
BEGIN

  SELECT sum(payment_amount) * -1 INTO total_amount FROM quittances
  WHERE order_id = NEW.id;

  INSERT INTO "quittances" (order_id, TYPE, payment_amount)
  VALUES (NEW.id, 'отмена', total_amount) RETURNING id INTO new_quittance_id;

  INSERT INTO "notify" (customer_id, order_id, quittance_id, is_paid)
  VALUES (NEW.customer_id, NEW.id, new_quittance_id, FALSE);

  RETURN NEW;
END;
$body$
LANGUAGE 'plpgsql';

CREATE TRIGGER orders_tr AFTER UPDATE OF is_cancel ON public.orders
FOR EACH ROW EXECUTE PROCEDURE orders_update_is_cancel_after_tr();

-- Позиция товара (position):

-- drop table public."order_position";

CREATE TABLE public."order_position" (
  order_id INTEGER  NOT NULL,
  product_id INTEGER REFERENCES public.products(id) NOT NULL,
  count_products INTEGER CHECK (count_products > 0),
  FOREIGN KEY (order_id) REFERENCES public."orders"(id),
  PRIMARY KEY(order_id)
);

COMMENT ON COLUMN public."order_position".order_id IS 'ID заказа';
COMMENT ON COLUMN public."order_position".product_id IS 'ID товара';

-- ##################################################
-- ##################################################
-- ##################################################


-- Документ об оплате (quittances):

-- drop table "quittances" cascade;

CREATE TABLE public."quittances" (
  id SERIAL,
  order_id INTEGER REFERENCES public."orders"(id) NOT NULL,
  type VARCHAR(100),
  payment_datetime TIMESTAMP(0) WITHOUT TIME ZONE DEFAULT now() NOT NULL,
  payment_amount NUMERIC,
  PRIMARY KEY(id)
);

COMMENT ON COLUMN public."quittances".id IS 'ID документа об оплате';
COMMENT ON COLUMN public."quittances".order_id IS 'ID заказа';
COMMENT ON COLUMN public."quittances".type IS 'тип документа';
COMMENT ON COLUMN public."quittances".payment_datetime IS 'дата и время оплаты';
COMMENT ON COLUMN public."quittances".payment_amount IS 'сумма оплаты';

-- Оповещение (notify):

-- drop table "notify" cascade;

CREATE TABLE public."notify" (
  id SERIAL,
  customer_id INTEGER REFERENCES public.customers(id) NOT NULL,
  order_id INTEGER REFERENCES public."orders"(id) NOT NULL,
  quittance_id INTEGER REFERENCES public."quittances"(id),
  datetime_send TIMESTAMP(0) WITHOUT TIME ZONE DEFAULT now() NOT NULL,
  date_end_purchase TIMESTAMP(0) WITHOUT TIME ZONE,
  is_paid BOOLEAN DEFAULT FALSE,
  PRIMARY KEY(id)
);

COMMENT ON COLUMN public."notify".id IS 'ID оповещения';
COMMENT ON COLUMN public."notify".customer_id IS 'ID покупателя';
COMMENT ON COLUMN public."notify".order_id IS 'ID заказа';
COMMENT ON COLUMN public."notify".quittance_id IS 'ID квитанции';
COMMENT ON COLUMN public."notify".datetime_send IS 'дата и время отправки оповещения';
COMMENT ON COLUMN public."notify".date_end_purchase IS 'крайний срок выкупа товара';
COMMENT ON COLUMN public."notify".is_paid IS 'отметка об оплате товара';

-- ##################################################
-- ##################################################
-- ##################################################

-- Товарная накладная (waybill):

CREATE TABLE public."waybills" (
  id SERIAL,
  date_receipt DATE DEFAULT now() NOT NULL,
  total_product INTEGER CHECK (total_product > 0),
  total_cost NUMERIC CHECK (total_cost > 0),
  PRIMARY KEY(id)
);

COMMENT ON COLUMN public."waybills".id IS  'ID накладной';
COMMENT ON COLUMN public."waybills".date_receipt IS 'дата поступления товара';
COMMENT ON COLUMN public."waybills".total_product IS 'кол-во поступивщего товара';
COMMENT ON COLUMN public."waybills".total_cost IS 'всего отпущено на сумму';

-- Поставка (delivery):

CREATE TABLE public."deliveries" (
  waybill_id INTEGER REFERENCES public.waybills(id),
  product_id INTEGER REFERENCES public.products(id),
  count_products INTEGER CHECK (count_products > 0),
  PRIMARY KEY(waybill_id, product_id)
);

COMMENT ON COLUMN public.deliveries.waybill_id IS 'номер накладной';
COMMENT ON COLUMN public.deliveries.product_id IS 'код товара';
COMMENT ON COLUMN public.deliveries.count_products IS 'кол-во товаров';

CREATE OR REPLACE FUNCTION delevires_insert_after_tr ()
RETURNS trigger AS
$body$
BEGIN
  -- увеличиваем кол-во товаров на складе

  UPDATE products
  SET count_in_storage = count_in_storage - NEW.count_products
  WHERE id = NEW.product_id;

  RETURN NEW;
END;
$body$
LANGUAGE 'plpgsql';

CREATE TRIGGER deliveries_tr AFTER INSERT ON public.deliveries
FOR EACH ROW EXECUTE PROCEDURE public.delevires_insert_after_tr();





CREATE OR REPLACE FUNCTION public.product_cancel_analysis (
  in_product_id integer
)
RETURNS text AS
$body$
DECLARE
    r_product "public"."products";
    total_sale integer;
    cancel_sale integer;
BEGIN
    SELECT * INTO r_product FROM "public"."products" WHERE id = in_product_id;

    IF r_product.id IS NULL THEN
        RAISE EXCEPTION 'not found product with id = %', in_product_id;
    END IF;
    
    SELECT sum(pop.count_products) INTO total_sale FROM "public"."order_position" AS pop
    JOIN "public"."orders" AS p ON p.id = pop.order_id
    WHERE product_id = in_product_id;

    SELECT sum(pop.count_products) INTO cancel_sale FROM "public"."order_position" AS pop
    JOIN "public"."orders" AS p ON p.id = pop.order_id
    WHERE product_id = in_product_id AND p.is_cancel IS TRUE;

    IF cancel_sale > ( total_sale - cancel_sale ) THEN
      RAISE WARNING 'Cancel more then sale! total = %; canceled = %', total_sale, cancel_sale;
        UPDATE "public"."products" SET is_defect = TRUE WHERE id = in_product_id;
        RETURN 'Product is not ok, update defect = true';
    END IF;

  RAISE WARNING 'Total less than canceled; total = %; canceled = %', total_sale, cancel_sale;
    RETURN 'Product is ok';
END;
$body$
LANGUAGE 'plpgsql';





CREATE OR REPLACE FUNCTION public.auto_notify (
  order_date date
)
RETURNS text AS
$body$
DECLARE
    r_order   "public"."orders";
    r_quittance "public"."quittances";

    order_cur NO SCROLL CURSOR (order_date date) FOR
        SELECT * FROM "public"."orders" AS "order"
        WHERE date_trunc('day', "order".datetime_registration) = order_date
        AND NOT EXISTS (SELECT id FROM "public"."notify" WHERE order_id = "order".id);
BEGIN

    OPEN order_cur(order_date);
    LOOP
      FETCH order_cur INTO r_order;
      EXIT WHEN NOT FOUND;

      RAISE WARNING 'Generate notify for order with id = %', r_order.id;
        
        -- Если есть квитанция, то создаем оповещение с ней
        SELECT id INTO r_quittance FROM "public"."quittances" WHERE order_id = r_order.id;
        
        IF r_quittance.id IS NOT NULL THEN
            INSERT INTO "public"."notify" (order_id, customer_id, quittance_id)
            VALUES (r_order.id, r_order.customer_id, r_quittance.id);
        ELSE 
            INSERT INTO "public"."notify" (order_id, customer_id)
            VALUES (r_order.id, r_order.customer_id);
        END IF;
    END LOOP;
    CLOSE order_cur;
    
  return 'All notify is generated';
END;
$body$
LANGUAGE 'plpgsql';
