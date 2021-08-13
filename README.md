# Projeto
## Sistema de Streaming

Uma empresa de streaming de filmes está contratando você para desenvolver uma parte de seu sistema. Segue abaixo as especificações que você deve seguir para desenvolver o sistema solicitado. 
## Entidades
Inicialmente, é necessário entender as entidades envolvidas no processo, as quais são descritas abaixo:

- **Cliente:** Um cliente é uma pessoa que possui um **código único** (chave de busca), **nome**, **e-mail**, **telefone** e **status** (ativo ou inativo). O telefone segue o formato: 19-9-XXXX-XXXX. Para facilitar, supõe-se que é possível cadastrar no **máximo 10 clientes**. O código deverá ser gerado automaticamente (auto incremento) e começará na numeração 1001.  

- **Filme:** Um filme é descrito pelas seguintes características: um **código único** (chave de busca), **nome**, **gênero** e **classificação**. Os gêneros possíveis são: *aventura*, *comedia*, *drama*, *terror*, *ação* e *romance*. As classificações possíveis são: *livre*, *proibido para menores de 10 anos*, *menores de 12*, *menores de 14*, *menores de 16* e *menores de 18*. Para facilitar, supõe-se que é possível cadastrar no **máximo 10 filmes**. O código deverá ser gerado automaticamente (auto incremento) e começará na numeração 2001.
- **Planos:** Existem dois tipos: **Básico** e **premium**. O plano básico é descirto pelas seguintes características: **Quantidade de filmes** que o cliente pode assistir por mês, **valor base do plano** e **valor excedente** por filme adicional assistido (acima da quantidade que o cliente tem direito). O plano premium é descrito pela seguinte característica: **valor base do plano**.
- **Contrato**: Um contrato é descrito pelas seguintes características: **código do cliente** relacionado ao contrato (chave de busca), **tipo do plano contratado** (básico ou premium), *data da contratação*, *data do cancelamento* e *tipo de pagamento (crédito ou débito)*. Caso o tipo de pagamento seja crédito armazena-se o **número do cartão de crédito**; caso seja débito armazena-se o **número da agência** e o *número da conta* para débito automático. As datas são compotas por dia e mês (exibir para o usuário no formato dd/mm). Enquanto o contrato não é cancelado a data de cancelamento fica em 00/00/00. Para facilitar, supõe-se que é possível cadastrar no **máximo 10 contratos**.
- **Histórico Mensal:** O sistema deverá armazenar, para cada cliente, seu histórico mensal de filmes assistidos. Assim, haverá uma matriz 10X30 em que cada célula da matriz armazena o **código do filme** assistido, assim como a **data** em que o cliente assistiu ao filme (note que cada linha representa um cliente). Para facilitar, supõe-se que um cliente irá assistir ao no **máximo 30 filmes** no mês (por isso a matriz é 10X30).
## Funcionalidades
