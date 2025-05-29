Library IEEE;
USE IEEE.Std_logic_1164.all;

entity robot is
    port(
        input_seq : in std_logic_vector := "1011"; -- Default value for input_seq is 1011 (ist die Sequenz die untersucht wird)
        Clk : in std_logic;
        y : out Boolean  -- TRUE wenn 1011 in der Sequenz erkannt wird
    );
    end robot;

architecture behavioral of robot is
    
    
    begin
        process(Clk, input_seq)
        variable counter : integer := input_seq'length - 1;
            type Zustaende is (Z1, Z2, Z3, Z4);
            variable Zustand : Zustaende;
            begin
                
                if(rising_edge(Clk)) then  -- fuer jede steigende Taktflanke wird ein Element der Eingabesequenz abgegangen
                    if(counter >= 0) then
                    case Zustand is
                        when Z1 =>
                            if input_seq(counter) = '1' then
                                Zustand := Z2;
                                y <= false;
                            else y <= false;
                            end if;
                        when Z2 =>
                            if input_seq(counter) = '0' then
                                Zustand := Z3;
                                y <= false;
                            else y <= false; -- für 1 bleibt man im Zustand Z2
                            end if;
                        when Z3 =>
                            if input_seq(counter) = '1' then
                                Zustand := Z4;
                                y <= false;
                            else 
                            Zustand := Z1;
                            y <= false;
                            end if;
                        when Z4 =>
                            if input_seq(counter) = '1' then
                                Zustand := Z2;
                                y <= true;
                            else
                                Zustand := Z3;
                                y <= false;
                            end if;
                    end case;
                    counter := counter -1;
                    end if;
                end if;
                
        end process;
    end behavioral;
    
