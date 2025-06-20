import java.io.IOException;
import java.util.List;

public interface IFancyWriter{
	
	void writeLine(String line) throws IOException;

	void writeLines(List<String> lines) throws IOException;

}
