var express=require('express')
var app=express()
var body_parser=require('body-parser')

var banco_unibio=require('./banco_unibio.js')

app.use(body_parser.json())
app.use(function (err, req, res, next) {
  console.error(err)
  res.status(400).send('Problema nos dados recebidos.')
})

app.route('/central/:cod_central/biodigestor/:cod_biodigestor').post(async (req,res)=>{
    try {
        const cod_central=req.params.cod_central
        const cod_biodigestor=req.params.cod_biodigestor
        console.log('\nRequisição de biodigestor, inserir dados:')
        console.log('\tCentral : '+cod_central)
        console.log('\tBiodigestor : '+cod_biodigestor)
        console.log('\tDados : ')
        req.body.forEach(
            obj=>
            {
                for(var chave in obj)
                    console.log('\t\t'+chave+' : '+obj[chave])
                console.log()
            }
        )
        const result=await banco_unibio.inserir_leituras_array(cod_central,cod_biodigestor,req.body)
        console.log('\tSucesso ao inserir : '+ result)
        res.status(200).send('ok')
    } 
    catch (error) {
        console.log('\tFalha ao inserir : '+ error)    
        res.status(500).send('err')
    }
})
app.route('/central/:cod_central/biodigestor/:cod_biodigestor/sensor/:nome_sensor').get(async (req,res)=>{
    try
    {
        const cod_central=req.params.cod_central
        const cod_biodigestor=req.params.cod_biodigestor
        const nome_sensor=req.params.nome_sensor
        const result=await banco_unibio.todas_leituras_sensor(cod_central,cod_biodigestor,nome_sensor)
        res.status(200).send(result)
    }
    catch(err)
    {
        console.log(err)
        res.status(500).json(err)
    }
})

app.listen(8000,()=>console.log('API UniBio iniciado em http://localhost:8000'))
