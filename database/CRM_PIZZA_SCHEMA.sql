CREATE TABLE tbl_Cliente(
    ID_Cliente_PK   VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome            VARCHAR(100), 
    Sobrenome       VARCHAR(100)
);
CREATE TABLE tbl_Telefone_Cliente(
    ID_Telefone_PK  VARCHAR(10) NOT NULL PRIMARY KEY,
    ID_Cliente_FK   VARCHAR(10),
    Num_Telefone    INTEGER,

    FOREIGN KEY(ID_Cliente_FK)
        REFERENCES tbl_Cliente(ID_Cliente_PK)
);
CREATE TABLE tbl_Endereco_Cliente(
    ID_Endereco_PK   VARCHAR(10) NOT NULL PRIMARY KEY,
    Rua              VARCHAR(50),
    Num_Casa         VARCHAR(10),
    Bairro           VARCHAR(50),
    Cidade           VARCHAR(50),
    ID_Cliente_FK    VARCHAR(10),

    FOREIGN KEY(ID_Cliente_FK)
        REFERENCES tbl_Cliente(ID_Cliente_PK)
);
CREATE TABLE tbl_Status_Pedido(
    ID_Status_Pedido_PK     VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome_Status_Pedido      VARCHAR(25)
);
CREATE TABLE tbl_Pedido(
    ID_Pedido_PK            VARCHAR(10) NOT NULL PRIMARY KEY,
    Data                    DATE,
    Hora                    TIME,
    ID_Cliente_FK           VARCHAR(10),
    ID_Status_Pedido_FK     VARCHAR(10),

    FOREIGN KEY(ID_Cliente_FK)
        REFERENCES tbl_Cliente(ID_Cliente_PK),

    FOREIGN KEY(ID_Status_Pedido_FK)
        REFERENCES tbl_Status_Pedido(ID_Status_Pedido_PK)
);
CREATE TABLE tbl_Tipo_Pizza(
    ID_Tipo_Pizza_PK    VARCHAR(10) NOT NULL PRIMARY KEY, 
    Nome_Tipo           VARCHAR(25)
);
CREATE TABLE tbl_Sabor_Pizza(
    ID_Sabor_PK         VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome_Pizza          VARCHAR(100),
    Preco               NUMERIC, 
    ID_Tipo_Pizza_FK    VARCHAR(10),

    FOREIGN KEY(ID_Tipo_Pizza_FK)
        REFERENCES tbl_Tipo_Pizza(ID_Tipo_Pizza_PK)
);
CREATE TABLE IF NOT EXISTS "tbl_Itens_Pedido"(
    ID_Item_PK      VARCHAR(10) NOT NULL PRIMARY KEY,
    Qtd             INT,
    Preco_Unit      NUMERIC,
    ID_Sabor_FK     VARCHAR(10),
    ID_Pedido_FK    VARCHAR(10),

    FOREIGN KEY(ID_Sabor_FK)
        REFERENCES tbl_Sabor_Pizza(ID_Sabor_PK),

    FOREIGN KEY(ID_Pedido_FK)
        REFERENCES tbl_Pedido(ID_Pedido_PK)
);
CREATE TABLE tbl_Ingredientes(
    ID_Ingrediente_PK   VARCHAR(10) NOT NULL PRIMARY KEY, 
    Nome_Ingrediente    VARCHAR(100)
);
CREATE TABLE tbl_Pizza_Ingredientes(
    ID_Pizza_Ingrediente_PK     VARCHAR(10) NOT NULL PRIMARY KEY,
    ID_Sabor_FK                 VARCHAR(10),
    ID_Ingrediente_FK           VARCHAR(10),

    FOREIGN KEY(ID_Sabor_FK)
        REFERENCES tbl_Sabor_Pizza(ID_Sabor_PK),

    FOREIGN KEY(ID_Ingrediente_FK)
        REFERENCES tbl_Ingredientes(ID_Ingrediente_PK)
);
CREATE TABLE tbl_Status_Comanda(
    ID_Status_Comanda_PK    VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome_Status_Comanda     VARCHAR(100)
);
CREATE TABLE tbl_Comanda(
    ID_Comanda_PK           VARCHAR(10) NOT NULL PRIMARY KEY,
    Hora_Abertura           TIME,
    Data_Fechamento         DATE,
    Hora_Fechamento         TIME,
    ID_Cliente_FK           VARCHAR(10),
    ID_Pedido_FK            VARCHAR(10),
    ID_Status_Comanda_FK    VARCHAR(10),
    
    FOREIGN KEY(ID_Cliente_FK)
        REFERENCES tbl_Cliente(ID_Cliente_PK),
        
    FOREIGN KEY(ID_Pedido_FK)
        REFERENCES tbl_Pedido(ID_Pedido_PK),
        
    FOREIGN KEY(ID_Status_Comanda_FK)
        REFERENCES tbl_Status_Comanda(ID_Status_Comanda_PK)
);
