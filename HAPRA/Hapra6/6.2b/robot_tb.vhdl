library ieee;
use ieee.std_logic_1164.all;

entity robot_tb is
end robot_tb;

architecture behavioral of robot_tb is
    component robot is
        port(
            input_seq : in std_logic_vector := "1011"; -- Default value for input_seq is 1011;
            Clk : in std_logic;
            y : out Boolean
        );
        end component;

        signal i : std_logic_vector(6 downto 0); -- Test an Sequenz der Länge 6
        signal Cl : std_logic;
        signal yo : boolean;

        begin
            r : robot port map(i, Cl, yo);

            process begin
                i <= "1011011";
                Cl <= '0';
                wait for 10 ns;

                Cl <= '1';
                wait for 10 ns;
                
                Cl <= '0';
                wait for 10 ns;

                Cl <= '1';
                wait for 10 ns;
                Cl <= '0';
                wait for 10 ns;

                Cl <= '1';
                wait for 10 ns;
                Cl <= '0';
                wait for 10 ns;

                Cl <= '1';
                wait for 10 ns;
                Cl <= '0';
                wait for 10 ns;

                Cl <= '1';
                wait for 10 ns;
                Cl <= '0';
                wait for 10 ns;

                Cl <= '1';
                wait for 10 ns;
                Cl <= '0';
                wait for 10 ns;
                Cl <= '1';
                wait for 10 ns;

                wait;
                end process;
    end behavioral;
