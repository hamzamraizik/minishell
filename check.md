
{1}

Minishell -> echo "Hello " > out > hello >
echo =====>     WORD
"Hello " =====> WORD
> =====>        OUT
out =====>      WORD
> =====>        OUT
hello =====>    WORD
PA� =====>      WORD 

{2}
Minishell -> > > >
Minishell ->  //fin output ?


{3}
Minishell -> << "EOF" echo "some text" > out1 > out2
<< =====>       HEREDOC
"EOF" =====>    WORD        <<//!!!!! specifi type dyalo l like : "EOF_HERD" 
echo =====>     WORD
"some text" =====>      WORD
> =====>        OUT
out1 =====>     WORD
> =====>        OUT
out2 =====>     WORD


{4}
Minishell -> echo $name
echo =====>     WORD
 =====> WORD  << specify the name as type :> variable

 {4}
 Minishell -> echo -e
echo =====>     WORD
-e =====>       WORD << zid liys type : -e = "flag" 

{5}
Minishell -> echo "hello world $NAME"
echo =====>     WORD
hello world  =====>     WORD  << were is **{NAME}** ? 
Minishell -> echo "hello world $$NAME"
echo =====>     WORD
"hello world $$NAME" =====>     WORD 