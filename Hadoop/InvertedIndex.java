import java.io.IOException;
import java.util.StringTokenizer;
import java.util.HashSet;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.io.MapWritable;

public class InvertedIndex {

  	public static class MyMapper extends Mapper<Object, Text, Text, Text>{
 
     	  	 private Text word = new Text();

    		public void map(Object key, Text value, Context context) throws IOException, InterruptedException {

			FileSplit filesplit = (FileSplit) context.getInputSplit();
     	  		String fileName = filesplit.getPath().getName();
			Text name = new Text();
			name.set(fileName);

      			StringTokenizer itr = new StringTokenizer(value.toString());

      			while (itr.hasMoreTokens()) {
				word.set(itr.nextToken());
				context.write(word, name);
      			}
		}
 
	 }
	
	public static class MyReducer extends Reducer<Text,Text,Text,Text> {
		
		

    		public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
      			String doc ="";

      			for (Text val : values) {
        			doc = doc.toString() + " , "+val.toString();
      			}
			Text docId = new Text(doc);
			
      			context.write(key, docId);
    		}
  	}

  	public static void main(String[] args) throws Exception {
    		Configuration conf = new Configuration();
    		Job job = Job.getInstance(conf, "landa inverted index");

    		job.setJarByClass(InvertedIndex.class);
    		job.setMapperClass(MyMapper.class);
    		job.setCombinerClass(MyReducer.class);
    		job.setReducerClass(MyReducer.class);
    		job.setOutputKeyClass(Text.class);
    		job.setOutputValueClass(Text.class);
    		FileInputFormat.addInputPath(job, new Path(args[0]));
    		FileOutputFormat.setOutputPath(job, new Path(args[1]));

    		System.exit(job.waitForCompletion(true) ? 0 : 1);
  	}
}