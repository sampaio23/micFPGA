
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_arith.ALL;
use IEEE.STD_LOGIC_unsigned.ALL;


entity Lab1 is
	port( DIPSW: in std_logic_vector(3 downto 0);
			BUTTON:  in std_logic;
			LEDS: out std_logic_vector(3 downto 0);
			CLK27M: in std_logic;
			TX : out std_logic;
			RX : in std_logic;
			VC : out std_logic;
			GN : out std_logic;
			ENT : in std_logic;
			RELECaio: out std_logic;
			RELE: out std_logic);
end Lab1;

architecture Behavioral of Lab1 is
signal clkRX, clkTX, recebendo : std_logic;
signal cont, cont2 : std_logic_vector (23 downto 0);
signal cont160 : std_logic_vector (7 downto 0);
signal prox, atual, palavra : std_logic_vector (9 downto 0);

begin
	VC <= '1';
	GN <= '0';
	
	LEDS(3) <= ENT;
	LEDS(2) <= ENT;
	LEDS(1) <= ENT;
	LEDS(0) <= ENT;
	
	process(CLK27M)
		begin 
			if(CLK27M' event and CLK27M = '1') then
			cont <= cont + "000000000000000000000001";
			cont2 <= cont2 + "000000000000000000000001";
				if(cont = "000000000000101011111100") then
					cont <= "000000000000000000000000";
				end if;
				if(cont2 = "000000000000000010110000") then
					cont2 <= "000000000000000000000000";
				end if;
			end if;
	end process;
	clkTX <= cont(11);         -- clkTX tem 9600 Hz
	clkRX <= cont2(7);         -- clkRX tem 9600 x 16 Hz
	
	prox <= "10" & DIPSW & "1100"	when BUTTON	= '1' else
				atual (8 downto 0) & '1';
	TX <= atual(9);
	
	process(clkTX)
		begin
		 if (clkTX' event and clkTX = '1') then
			atual <= prox;
		 end if;
	end process;
	
	process(clkRX)
		begin
		 if (clkRX' event and clkRX = '1') then
			if(recebendo = '0') then
			if(RX = '1') then
				cont160 <= "00000000";
			else
				recebendo <= '1'; --detecção do START BIT
			end if;
		end if;
			if(recebendo = '1') then
				cont160 <= cont160 + "0000001";
				if(cont160(3 downto 0) = "1000") then
					palavra <= RX & palavra (9 downto 1);
				end if;
				if (cont160 = "10011100") then recebendo <= '0';
					--LEDS <= palavra (4 downto 1);
					RELE <= palavra(1);
					RELECaio <= palavra(3);
				end if;
			end if;
		end if;
	end process;
	
end Behavioral;

