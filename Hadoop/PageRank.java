import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class PageRank {

  	public static class MyMapper extends Mapper<Text, Text, Text, Text>{
	 
      		private Text link  = new Text();
		private Text pagerank = new Text();
		private Text outLink = new Text();
		private Text outlinkList = new Text();
		private Boolean cle = true;
		private Integer sizelinks = 0;
		private Integer i = 0 ;
		private Float valeure;
		private Text valueText = new Text();

    		public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
      			StringTokenizer itr = new StringTokenizer(value.toString(),"\t");
			String myKey = itr.nextToken();
			String myValue = itr.nextToken();
			
			link.set(myKey.split(",")[0]);
			pagerank.set(myKey.split(",")[1]);
					
			outlinkList.set(myValue.toString());
			String[] outlinklist = myValue.split(",");
			valeure = new Float(Float.parseFloat(pagerank.toString()) / outlinklist.length);
			
			for(i = 0; i < outlinklist.length ; i++) {
				outLink.set(outlinklist[i]);
				valueText.set(valeure.toString());
				context.write(outLink,valueText);
			}
			
			context.write(link,outlinkList);				
		}
				
 
	   }
	
	public static class MyReducer extends Reducer<Text,Text,Text,Text> {
		private Text outlinkList = new Text();
		private Text cle = new Text(); 
		private Float pagerank = 0f;

    		public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
      		
			for (Text val : values) {
				if( Float.parseFloat(val.toString().split(",")[0])< 1 ){
					pagerank += Float.parseFloat(val.toString().split(",")[0]);
				} 
				else {
					outlinkList = val;
				}
			}
				pagerank = 1f - 0.85f + (0.85f * pagerank); 
				cle.set(key.toString() + ","+ Float.toString(pagerank) );
	      			context.write(cle, outlinkList);
	
	    		}
  	}

  	public static void main(String[] args) throws Exception {
    		Configuration conf = new Configuration();
    		Job job = Job.getInstance(conf, "landa page rank");

    		job.setJarByClass(PageRank.class);
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