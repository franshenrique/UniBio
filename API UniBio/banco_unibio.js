var mysql = require('mysql')
var util = require('util')

var pool = mysql.createPool(
    {
        host : 'localhost',
        user : 'unibio',
        password: 'unibio10@',
        multipleStatements: true
    }
)

var simple_query=util.promisify((sql_query,callback)=>
{
    pool.query(sql_query,(err,results)=>{
        callback(err,results)
    })
})
var conn_query=util.promisify((sql_query,connection,callback)=>
{
    connection.query(sql_query,(err,results)=>{
        callback(err,results)
    })
})
var get_conn=util.promisify((callback)=>{
    pool.getConnection((err,connection)=>{
        callback(err,connection)
    })
})

exports.inserir_leituras_array=async function(cod_central,cod_biodigestor,dados,callback)
{
    var insertedRows=0
    try{
        var conn=await get_conn()
        try{
            await conn_query('USE central_'+cod_central+' ;',conn)
            await conn_query('START TRANSACTION;',conn)
            var insert=' INSERT INTO biodigestor_'+cod_biodigestor
            insert+='(data_hora,temp_amb,temp_bm,temp_gas,umidade,pressao,metano,sulfidrico,carbono)'
            insert+=' VALUES(?,?,?,?,?,?,?,?,?);'
            for(const ele of dados)
            {
                var values=[ele.data_hora,ele.temp_amb,ele.temp_bm,ele.temp_gas,ele.umidade,ele.pressao,ele.metano,ele.sulfidrico,ele.carbono]
                var p_insert=mysql.format(insert,values)
                var result=await conn_query(p_insert,conn)
                insertedRows+=result.affectedRows
            }
            await conn_query('COMMIT;',conn)
        }
        catch(err){
            await conn_query('ROLLBACK;',conn)
            throw err
        }
        finally{
            conn.release()
        }
    }
    catch(err){
        console.log(err)
        throw err
    }
    return insertedRows
}
exports.todas_leituras_sensor=async function(cod_central,cod_biodigestor,nome_sensor)
{
    try{
        var sql='USE central_'+cod_central+';SELECT CONVERT(data_hora,CHAR(20)) AS data_hora, '+nome_sensor+' FROM biodigestor_'+cod_biodigestor+';'
        var results=await simple_query(sql)
        return results[1]
    }
    catch(err){
        console.log(err)
        throw err
    }
}
